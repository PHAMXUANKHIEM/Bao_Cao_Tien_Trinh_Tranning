# Zone Features

1. Tổng quan

- Zone Features là các cờ flag được cấu hình trong file `zone.json`. Nó khai báo cho toàn bộ cụm Ceph biết rằng zone này đang được hỗ trợ các tính năng gì

- Sinh ra để giải quyết bài toán đồng bộ  đa vùng (Multi-site)

2. Các loại support features
  
- resharding (Reef): Cho phép bật tính năng Dynamic Bucket Resharding để chia nhỏ bucket thành các shard tránh việc bucket quá lớn gây tắc cổ chai

- compress-encrypted (Reef): Cho phép nén object ngay cả khi nó được mã hóa SSE

- Notification_v2 (Squid): Cho phép RGW bắn thông báo ra ngoài khi thay đổi trong Bucket

![](images_RADOS/anh84.png)


3. Cấu hình bật tính năng

- Thêm tính năng
```sh
radosgw-admin zonegroup modify --enable-feature=compress-encrypted
radosgw-admin zonegroup modify --enable-feature=resharding
```

![](images_RADOS/anh85.png)

- Xóa tính năng

```sh
radosgw-admin zonegroup modify --disable-feature=compress-encrypted
```
![](images_RADOS/anh86.png)
