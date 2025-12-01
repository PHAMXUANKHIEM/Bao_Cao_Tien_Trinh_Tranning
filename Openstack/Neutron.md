# Neutron

## 1. Khái niệm
Neutron là thành phần quản lý mạng trong OpenStack, cung cấp dịch vụ mạng ảo (virtual networking) cho các máy ảo và tài nguyên đám mây.

Mục đích:
- Tạo, quản lý và cấu hình mạng ảo, cổng mạng, và các dịch vụ mạng.
- Hỗ trợ các mô hình mạng phức tạp: VLAN, VXLAN, overlay, v.v.
- Tích hợp với Nova và Cinder để phục vụ yêu cầu mạng của VM.

## 2. Cách hoạt động
Quy trình xử lý yêu cầu mạng:
1. Xác thực và ủy quyền yêu cầu từ người dùng.
2. Neutron Server xử lý API và tạo các tài nguyên mạng cần thiết.
3. Neutron Agents cấu hình các thành phần mạng trên compute nodes hoặc network nodes.
4. Neutron theo dõi trạng thái và quản lý lifecycle của tài nguyên mạng.

## 3. Tính năng chính
- Quản lý mạng ảo (networks, subnets, ports).
- Hỗ trợ nhiều mô hình và driver mạng (Open vSwitch, Linux Bridge...).
- Các dịch vụ mạng nâng cao: routing, load balancing, firewall, VPN.
- Khả năng mở rộng và plugin để tích hợp với thiết bị mạng phần cứng hoặc phần mềm.

## 4. Ứng dụng
- Cung cấp mạng cho VM, phân đoạn mạng, bảo mật mạng theo tenant.
- Triển khai mạng phức tạp cho hạ tầng đám mây doanh nghiệp.