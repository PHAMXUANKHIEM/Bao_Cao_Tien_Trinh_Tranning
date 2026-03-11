# POOL PLACEMENT VÀ STORAGE CLASS
## STORAGE CLASS 

1. Khái niệm

- Là bộ phận phân loại logic được gán cho từng object nhằm quyết định cách thức và vị trí vật lý mà dữ liệu sẽ được lưu ở tầng dưới cùng (Nói dễ hiểu nó sẽ quyết định object của ta sẽ được lưu vào ổ cứng loại nào để tối ưu hiệu suất và chi phí)

2. Các lớp Storage Class 

- STANDARD (Lớp tiêu chuẩn): Lớp mặc định có hiệu suất cao nhất, độ trễ thấp nhất dành riêng cho dữ liệu được truy cập thường xuyên. Các ổ cứng khuyên dùng cho loại dữ liệu này là NVMe SSD hoặc SATA/SAS SSD

- STANDARD_IA: Dành cho dữ liệu ít truy cập nhưng khi cần thì phải lấy được ngay lập tức. Ổ cứng khuyên dùng cho loại này là QLC SSD hoặc SAS

- GLACIER / ARCHIVE: Đây là lớp lưu trữ lạnh, chi phí rẻ nhưng khi muốn lấy file ra hệ thống có thể mất từ vài phút đến vài giờ để rã đông dữ liệu. Các ổ cứng khuyên dùng là NL-SAS / SATA

- DEEP ARCHIVE: Đây là lớp lưu trữ dữ liệu đóng băng và gần như không bao giờ được truy cập, chỉ dùng làm phương án khôi phục thảm họa. THời gian lấy ra có thể mất từ vài giờ đến vài ngày. Các ổ cứng khuyên dùng SMR HDD, Băng từ 

## POOL PLACEMENT

### Placement targets

1. Định nghĩa

- Là một cấu trúc định tuyến giúp phân giải và ánh xạ từ một bucket logic  của S3 tới các pool cụ thể trong Ceph. Nó sẽ chỉ định phần cứng nào sẽ lưu Index Pool (Metadata)

- Được chỉ định ngay sau khi tạo Bucket. Nếu Bucket không được chỉ định khi tạo, nó sẽ tự động gán là default-placement và không thể thay đổi được nó

2. Các thành phần mà Placement sẽ quyết định này nằm ở ổ cứng nào

- Index Pool: tên mặc định là `default.rgw.buckets.index` ghi chép lại danh sách toàn bộ các file đang nằm trong nó.

- Data Extra Pool: Nơi chứa các mảnh dữ liệu chưa hoàn chỉnh khi upload 1 file lớn (Multipart Upload)
 
- Danh sách chứa Storage Class cho phép: Khai báo rõ bucket nào dùng placement này sẽ được di chuyển dữ liệu vào lớp STANDARD hay COLD

3. Các loại mô hình chia Placement 

  - Default-placement (Mặc định): trỏ tất cả các Index pool vào `default.rgw.buckets.index` và dữ liệu vào `default.rgw.buckets.data`

  - Performance-based Placement (Phân loại theo hiệu suất ổ cứng): 

    - Loại Premium: cấu hình `index_pool` trỏ tới cụm NVMe, danh sách storage_classes bên trong chỉ cho phép trỏ tới các data_pool dùng NVMe hoặc SSD Enterprise.

    - Loại Capacity: cấu hỉnh `index_pool` trỏ tới cụm SSD SATA thông thường (để đảm bảo list file không bị treo), nhưng storage_classes mặc định bị ép trỏ thẳng xuống các data_pool dùng HDD quay cơ học chạy thuật toán mã hóa xóa (Erasure Coding).
## Câu hình

1. Tạo các RADOS Pools ở tầng Vật lý

```sh
# 1. Tạo Index Pool (Bắt buộc dùng SSD/NVMe)
ceph osd pool create rgw.premium.index 64 64
ceph osd pool set rgw.premium.index crush_rule ssd_rule

# 2. Tạo Data Extra Pool (Dùng cho Multipart Upload rác, thường dùng SSD)
ceph osd pool create rgw.premium.non-ec 64 64
ceph osd pool set rgw.premium.non-ec crush_rule ssd_rule

# 3. Tạo Data Pool cho lớp STANDARD (Dùng SSD)
ceph osd pool create rgw.premium.standard.data 128 128
ceph osd pool set rgw.premium.standard.data crush_rule ssd_rule

# 4. Tạo Data Pool cho lớp COLD (Dùng HDD, ưu tiên dùng cấu hình Erasure Coding nếu có)
ceph osd pool create rgw.premium.cold.data 128 128
ceph osd pool set rgw.premium.cold.data crush_rule hdd_rule
```
2. Khai báo Zonegroup

```sh
# Thêm Placement Target vào Zonegroup mặc định
radosgw-admin zonegroup placement add --rgw-zonegroup=default --placement-id=premium-placement

# Thêm Storage Class COLD vào Placement vừa tạo (Lớp STANDARD mặc định đã có)
radosgw-admin zonegroup placement add --rgw-zonegroup=default --placement-id=premium-placement --storage-class=COLD
```

3. Ánh xạ (Mapping) tại Zone bằng file JSON

***Dùng Cephadm thì phải xuất file zone.json ra***

```sh
# Xuất file zone.json

radosgw-admin zone get --rgw-zone=default > zone.json

```

- Tìm đến mảng `placement_pools` và thêm khối cấu hình sau vào trong mảng đó

```sh
{
            "key": "premium-placement",
            "val": {
                "index_pool": "rgw.premium.index",
                "data_extra_pool": "rgw.premium.non-ec",
                "index_type": 0,
                "storage_classes": {
                    "STANDARD": {
                        "data_pool": "rgw.premium.standard.data"
                    },
                    "COLD": {
                        "data_pool": "rgw.premium.cold.data"
                    }
                }
            }
        }
```

4. Đẩy cấu hình ngược lại vào Cluster (Import)

```sh
radosgw-admin zone set --rgw-zone=default --infile zone.json
```
5. Cập nhật và khởi động lại

```sh
radosgw-admin period update --commit
ceph orch restart rgw.<tên-dịch-vụ-rgw>
```
