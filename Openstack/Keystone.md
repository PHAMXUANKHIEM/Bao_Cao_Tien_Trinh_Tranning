# Keystone

## 1. Khái niệm
Keystone là dịch vụ quản lý xác thực và ủy quyền trong OpenStack. Keystone quản lý người dùng, vai trò, token và catalog (danh sách dịch vụ và endpoints).

Mục đích:
- Cung cấp dịch vụ xác thực cho người dùng và dịch vụ.
- Quản lý vai trò và quyền truy cập tài nguyên.
- Hỗ trợ nhiều phương thức xác thực: username/password, token, chứng chỉ.

![](images/keystone/anh1.png)

## 2. Cách hoạt động
- Khi người dùng/dịch vụ yêu cầu xác thực, Keystone kiểm tra thông tin đăng nhập.
- Nếu thành công, Keystone phát token xác thực cho phép truy cập các dịch vụ OpenStack.
- Keystone cung cấp catalog service chứa endpoints của các dịch vụ khác.

![](images/keystone/anh2.png)

## 3. Ứng dụng
- Dùng trong mọi triển khai OpenStack để đảm bảo an ninh và kiểm soát truy cập.
- Quản lý người dùng, nhóm, vai trò và policy.

## 4. Cấu hình
###  Cai dat va cau hinh mariadb cho Keystone
- Trước khi cài đặt, cần chuẩn bị cơ sở dữ liệu (MySQL, PostgreSQL) và tạo database cho Keystone.
- Cai dat openstack-client de quan ly openstack:
```sh
   sudo apt update
   sudo apt install python3-openstackclient
```
- Cài đặt MariaDB:
```sh
   apt install mariadb-server 
```
- Tao Keystone database:
```sh
   MariaDB [(none)]> CREATE DATABASE keystone;
```
- Cap quyen truy cap cho user keystone: (Thay KEYSTONE_DBPASS bang mat khau thuc)
```sh
   MariaDB [(none)]> CREATE USER 'keystone'@'localhost' IDENTIFIED BY 'KEYSTONE-DBPASS';
   MariaDB [(none)]> GRANT ALL PRIVILEGES ON keystone.* TO 'keystone'@'localhost';
   MariaDB [(none)]> CREATE USER 'keystone'@'%' IDENTIFIED BY 'KEYSTONE-DBPASS';
   MariaDB [(none)]> GRANT ALL PRIVILEGES ON keystone.* TO 'keystone'@'%';
```

![](images/keystone/anh3.png)

### Cai dat va cau hinh Keystone
- Cài đặt Keystone qua gói quản lý (apt, yum).
```sh
   sudo apt update
   sudo apt install keystone 
```
- File cấu hình: `keystone.conf`.
- Cấu hình cơ sở dữ liệu để lưu người dùng, vai trò, token.
```sh
   [database]
   connection = mysql+pymysql://keystone:KEYSTONE_DBPASS@controller/keystone
```
- Cấu hình token:
```sh
   [token]
   provider = fernet
```
- Điền thông tin vào cơ sở dữ liệu dịch vụ Identity:
```sh
   su -s /bin/sh -c "keystone-manage db_sync" keystone
```
- Tạo khóa Fernet để mã hóa token:
```sh
   keystone-manage fernet_setup --keystone-user keystone --keystone-group keystone
   keystone-manage credential_setup --keystone-user keystone --keystone-group keystone
```
- Khoi động dịch vụ Identity (Thay thế ADMIN_PASSbằng mật khẩu phù hợp cho người dùng quản trị):
```sh
   keystone-manage bootstrap --bootstrap-password ADMIN_PASS \
  --bootstrap-admin-url http://controller:5000/v3/ \
  --bootstrap-internal-url http://controller:5000/v3/ \
  --bootstrap-public-url http://controller:5000/v3/ \
  --bootstrap-region-id RegionOne
```
- Cau hinh may chu Apache de chay Keystone:
```sh
   sudo apt install apache2 
   sudo cp /etc/keystone/wsgi-keystone.conf /etc/apache2/sites-available/
   sudo a2ensite wsgi-keystone
   sudo systemctl restart apache2
```
## 5. Bảo mật
- Sử dụng các phương thức xác thực mạnh (password + token, chứng chỉ).
- Mã hóa thông tin nhạy cảm (mật khẩu, token).
- Thiết lập chính sách mật khẩu và giới hạn quyền truy cập.
- Theo dõi và ghi log các hoạt động liên quan đến xác thực.

## 6. Tích hợp
- Keystone tích hợp với Nova, Neutron, Cinder, Glance... để cung cấp xác thực và danh mục dịch vụ.