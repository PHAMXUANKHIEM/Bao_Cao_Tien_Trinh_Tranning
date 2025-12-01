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
- Cài đặt Keystone qua gói quản lý (apt, yum).
```sh
   sudo apt update
   sudo apt install keystone python3-keystoneclient
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
- Cấu hình catalog service:
```sh
   [catalog]
   driver = sql
```
- Tạo service và endpoints cho các dịch vụ OpenStack khác.
```sh
   openstack service create --name nova --description "OpenStack Compute" compute
   openstack endpoint create --region RegionOne compute public http://controller:8774/v2.1
```
## 5. Bảo mật
- Sử dụng các phương thức xác thực mạnh (password + token, chứng chỉ).
- Mã hóa thông tin nhạy cảm (mật khẩu, token).
- Thiết lập chính sách mật khẩu và giới hạn quyền truy cập.
- Theo dõi và ghi log các hoạt động liên quan đến xác thực.

## 6. Tích hợp
- Keystone tích hợp với Nova, Neutron, Cinder, Glance... để cung cấp xác thực và danh mục dịch vụ.