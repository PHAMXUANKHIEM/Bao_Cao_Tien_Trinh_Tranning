# Nova

## 1. Khái niệm
OpenStack Nova là thành phần quản lý tính toán (Compute) trong OpenStack, chịu trách nhiệm cung cấp và quản lý vòng đời của các máy ảo (VM).

Mục tiêu:
- Triển khai, quản lý và mở rộng các VM một cách linh hoạt.
- Hỗ trợ nhiều hypervisor (KVM, Xen, VMware...).
- Tích hợp với Neutron, Cinder, Glance để cung cấp một hệ sinh thái đầy đủ.

## 2. Cách hoạt động
Khi người dùng yêu cầu tạo VM:
1. Xác thực qua Keystone.
2. Nova Scheduler chọn host phù hợp dựa trên tài nguyên và chính sách.
3. Nova Compute tạo và cấu hình VM trên hypervisor đã chọn.
4. Nova theo dõi trạng thái VM và cung cấp các hành động quản lý (start, stop, reboot, delete).

## 3. Thành phần chính
- Nova API: Endpoint REST để tương tác với Nova.
- Nova Scheduler: Quyết định nơi triển khai VM.
- Nova Compute: Quản lý vòng đời VM trên host.
- Nova Conductor: Trung gian xử lý các thao tác cần truy cập DB hoặc dịch vụ khác để giảm tải cho compute nodes.

## 4. Nova Compute
- Tương tác trực tiếp với hypervisor để tạo, khởi động, tắt, xóa VM.
- Quản lý tài nguyên CPU, RAM, lưu trữ cục bộ.
- Hỗ trợ tính năng như live migration, snapshot, resize.

## 5. Nova Scheduler
- Dùng thuật toán và policy để chọn host triển khai.
- Hỗ trợ các chính sách: least-loaded, random, filter-based, custom filters.
- Cập nhật liên tục trạng thái tài nguyên để ra quyết định chính xác.

## 6. Nova API
- Cung cấp các endpoint để tạo, quản lý VM.
- Tuân thủ chuẩn RESTful, hỗ trợ phương thức HTTP: GET, POST, PUT, DELETE.
- Xác thực qua Keystone và hỗ trợ versioning.

## 7. Nova Conductor
- Thực hiện các tác vụ liên quan tới DB hoặc tích hợp services, giúp tách bớt công việc khỏi Nova Compute.
- Cải thiện hiệu suất và độ tin cậy cho hệ thống phân tán.

## 8. Triển khai
Các bước triển khai cơ bản:
1. Cài đặt và cấu hình Keystone, Glance, Neutron trước.
2. Cài đặt và cấu hình Nova Controller (API, Scheduler, Conductor).
3. Cài đặt Nova Compute trên các host vật lý.
4. Cấu hình `nova.conf` và khởi động dịch vụ.
5. Kiểm tra và theo dõi hoạt động của Nova sau khi triển khai.

Tài liệu, các lệnh CLI và Horizon (giao diện web) thường được dùng để quản lý và kiểm tra trạng thái Nova.