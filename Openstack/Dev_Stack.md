# Dev_Stack
## Chuẩn bị 
- Ubuntu (22.04)
- Cập nhật hệ thống
```sh
apt update & apt upgrade -y
```
- Khởi động lại máy 
```sh
sudo reboot
```
## Cài đặt 
### Tạo user stack (khuyến nghị để tránh xung đột)
- Tạo user stack và tạo thư mục cho nó
```sh
sudo useradd -s /bin/bash -d /opt/stack -m stack
```
- Đặt quyên thực thi cho thư mục stack
```sh 
chmod +x /opt/stack
```
- Cấp sudo mà không cần pass cho user stack
```sh
echo "stack ALL=(ALL) NOPASSD:ALL" | sudo tee /etc/sudoers.d/stack
chmod 0440 /etc/sudoers.d/stack
```
-Chuyển sang người dùng stack
```sh
sudo -u stack -i
```
- Dowload Devstack
```sh
git clone https://opendev.org/openstack/devstack
cd devstack
```
- Tạo file local.conf cùng với 4 password của devstack
```sh
[[local|localrc]]
ADMIN_PASSWORD=secret
DATABASE_PASSWORD=$ADMIN_PASSWORD
RABBIT_PASSWORD=$ADMIN_PASSWORD
SERVICE_PASSWORD=$ADMIN_PASSWORD
```
- Cài đặt devstack:
```sh
./stack.sh
```
