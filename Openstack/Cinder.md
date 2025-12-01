# Cinder

## 1. Khái niệm
Cinder là thành phần quản lý lưu trữ khối (block storage) trong OpenStack, cung cấp dịch vụ lưu trữ cho các máy ảo và ứng dụng đám mây.
Mục đích chính của Cinder:
- Cung cấp dịch vụ lưu trữ khối linh hoạt và mở rộng cho máy ảo và ứng dụng.
- Hỗ trợ nhiều backend lưu trữ như LVM, NFS, iSCSI, và các hệ thống lưu trữ mạng (NAS).
- Tích hợp với các dịch vụ OpenStack khác (ví dụ Nova) để cung cấp lưu trữ khi cần thiết.

![](images/Cinder/anh1.png)

## 2. Cách hoạt động
Quy trình cơ bản khi tạo/gắn/xóa volume:
1. Xác thực và ủy quyền từ người dùng hoặc dịch vụ.
2. Cinder Scheduler phân tích yêu cầu và chọn backend lưu trữ phù hợp.
3. Cinder Volume Service tạo/gắn/xóa volume trên backend được chọn.
4. Cinder theo dõi trạng thái các volume và cung cấp chức năng quản lý (sao lưu, phục hồi...).

![](images/Cinder/anh2.png) 
## 3. Ứng dụng
Cinder được dùng để:
- Cung cấp ổ đĩa khối cho máy ảo.
- Hỗ trợ snapshot, backup và restore cho các volume.
- Tích hợp với Nova để cung cấp storage cho lifecycle của VM.

## 4. Cấu hình
- Cài đặt Cinder bằng các công cụ quản lý gói (apt, yum).
```sh
   sudo apt update
   sudo apt install cinder-api cinder-scheduler cinder-volume python3-cinderclient
```
- File cấu hình chính: `cinder.conf` nam tai  /etc/cinder/cinder.conf — cấu hình cơ sở dữ liệu, backend lưu trữ, authentication (Keystone), endpoints.
- Cấu hình database cho Cinder:
```sh
   [database]
   connection = mysql+pymysql://cinder:CINDER_DBPASS@controller/cinder
```
- Cấu hình backend trong `cinder.conf` để định tuyến volume tới storage phù hợp. Ví dụ cấu hình backend LVM:
```sh
[lvm]
volume_driver = cinder.volume.drivers.lvm.LVMVolumeDriver
volume_group = cinder-volumes
iscsi_protocol = iscsi
iscsi_helper = tgtadm
```
- Cấu hình Keystone để xác thực:
```sh
[keystone_authtoken]
auth_uri = http://controller:5000
auth_url = http://controller:35357
memcached_servers = controller:11211
auth_type = password
project_domain_name = Default
user_domain_name = Default
project_name = service
username = cinder
password = CINDER_PASS
```
- Cấu hình Logging & Scheduler trong `cinder.conf`:
```sh
[DEFAULT]
log_file = /var/log/cinder/cinder.log
scheduler_driver = cinder.scheduler.filter_scheduler.FilterScheduler
``` 
- Khởi động dịch vụ Cinder (API, Scheduler, Volume).
```sh
   sudo systemctl enable cinder-volume cinder-scheduler cinder-api
   sudo systemctl start cinder-volume cinder-scheduler cinder-api
```
- Kiểm tra Cinder sau khi triển khai.
 ```sh
   cinder service-list
   cinder list
```