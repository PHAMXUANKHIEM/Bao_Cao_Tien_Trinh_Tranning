# Test khả năng chịu lỗi

## Chuẩn bị và kịch bản test

Chuẩn bị 4 node Ubuntu 22.04/24.04:

  - Controller Node (linstor): IP 192.168.1.64 (Chạy LINSTOR Controller + Satellite)

  - Compute Node 1 (linstor1): IP 192.168.1.116

  - Compute Node 2 (linstor2): IP 192.168.1.131
  
  - 1 Node Openstack: 192.168.1.84

- Đã cài xong cụm Linstor và Openstack đã cấu hình Linstor làm backend cho Cinder

- Kịch bản thử nghiệm :
  - Dùng fio để liên tục thấy dòng I/O
  - TH1: Sập dịch vụ (trên 1 node, trên 2 node, trên 3 node)
  - Th2: Mất mạng hoặc sập server (trên 1 node, trên 2 node, trên 3 node)

## Thử nghiệm

Chạy fio trên VM và mở node linstor quan sát

```sh
fio --name=ha-test --filename=/dev/vdb --rw=write --bs=4k --ioengine=libaio --direct=1 --time_based --runtime=300s --rate_iops=100
```
- Test mức 1: Sập dịch vụ 

```sh
systemctl stop linstor-satellite.service

```
- Làm lần lượt trên các node linstor, mỗi lần tắt thì dùng lại lệnh fio để xem dến khi tắt hết cả 3 node linstor

- Dùng lệnh `resource` để xem 

```sh
linstor resource list
```

![](images_linstor/anh7.png)

--> Kết quả: Dù tắt 1, 2 thậm chí là 3 node, ta vẫn fio được mặc dù toàn bộ cụm đã báo là `Unknow`

--> Giải thích: 
- Do sự tách biệt hoàn toàn giữa Control Plane (Linstor) và Data 
Plane (DRBD). Linstor chỉ làm nhiệm vụ điều phối, không trực 
tiếp lưu dữ liệu nên nếu khi đã điều phối xong các volume vào các ổ cứng cho các linstor thì tắt đi cũng không ảnh hưởng tới việc ghi dữ liệu

- TH2: Mất mạng

  - Trên các node lần lượt tắt mạng dùng để kết nối DRBD đi, mỗi lần tắt thì dùng lại lệnh fio để quan sát

```sh
ip link set <tên_card_mạng>
```

- Kết quả: Khi tắt 1 hoặc 2 node bất kì ta vẫn có thể đẩy dữ liệu bình thường, chỉ có lúc tắt node controller thì quá sẽ bị khựng lại một lúc do cần bầu lại, chỉ khi cả 3 node đều mất mạng thì dòng dữ liệu đi xuống mới bị chặn lại ---> Lúc này lệnh `fio`
sẽ bị treo lại

- Giải thích: Do việc ghi dữ liệu do DRBD đảm nhiệm mà DRBD chạy trên tầng Kernel thông qua giao thức TCP/IP nên khi mất mạng các gói dữ liệu sẽ không thể truyền đi





















