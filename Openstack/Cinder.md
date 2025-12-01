# Cinder

## 1. Khái niệm
Cinder là thành phần quản lý lưu trữ khối (block storage) trong OpenStack, cung cấp dịch vụ lưu trữ cho các máy ảo và ứng dụng đám mây.
Mục đích chính của Cinder:
- Cung cấp dịch vụ lưu trữ khối linh hoạt và mở rộng cho máy ảo và ứng dụng.
- Hỗ trợ nhiều backend lưu trữ như LVM, NFS, iSCSI, và các hệ thống lưu trữ mạng (NAS).
- Tích hợp với các dịch vụ OpenStack khác (ví dụ Nova) để cung cấp lưu trữ khi cần thiết.

[](image/Cinder/anh1.png)

## 2. Cách hoạt động
Quy trình cơ bản khi tạo/gắn/xóa volume:
1. Xác thực và ủy quyền từ người dùng hoặc dịch vụ.
2. Cinder Scheduler phân tích yêu cầu và chọn backend lưu trữ phù hợp.
3. Cinder Volume Service tạo/gắn/xóa volume trên backend được chọn.
4. Cinder theo dõi trạng thái các volume và cung cấp chức năng quản lý (sao lưu, phục hồi...).

[](image/Cinder/anh2.png) 
## 3. Ứng dụng
Cinder được dùng để:
- Cung cấp ổ đĩa khối cho máy ảo.
- Hỗ trợ snapshot, backup và restore cho các volume.
- Tích hợp với Nova để cung cấp storage cho lifecycle của VM.

## 4. Cấu hình
- Cài đặt Cinder bằng các công cụ quản lý gói (apt, yum).
- File cấu hình chính: `cinder.conf` — cấu hình cơ sở dữ liệu, backend lưu trữ, authentication (Keystone), endpoints.
- Cấu hình backend trong `cinder.conf` để định tuyến volume tới storage phù hợp.