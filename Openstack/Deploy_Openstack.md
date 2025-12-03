# Triển khai OpenStack
## 1. Chuẩn bị môi trường
- Cài đặt hệ điều hành Ubuntu Server 22.04 trên tất cả các nút
Mô hình triển khai:
- Controller Node: Quản lý các dịch vụ OpenStack
- Compute Node: Chạy các máy ảo

![](images/deploy_openstack/anh1.png)

- Cập nhật hệ thống:
```sh
   sudo apt update && sudo apt upgrade -y
```
