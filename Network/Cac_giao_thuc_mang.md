# Các giao thức mạng (Các giao thức mạng)

## 1. Tổng quan
Mạng máy tính sử dụng nhiều giao thức ở các tầng khác nhau của mô hình OSI/TCP‑IP để truyền dữ liệu, quản lý kết nối và định tuyến.

## 2. Một số giao thức tiêu biểu
- Lớp liên kết (Link): ARP, Ethernet.
- Lớp mạng (Network): IP, ICMP.
- Lớp vận chuyển (Transport): TCP, UDP.
- Lớp ứng dụng (Application): HTTP, HTTPS, DNS, FTP, SSH.

## 3. Mục đích và tính năng
- TCP: kết nối, đảm bảo độ tin cậy (retransmission, flow control).
- UDP: không kết nối, thấp độ trễ, phù hợp real‑time.
- ICMP: kiểm tra, báo lỗi (ping, traceroute).
- DNS: phân giải tên miền → IP.

## 4. Ghi chú
- Hiểu rõ các giao thức giúp debug mạng (tcpdump, wireshark).
- Cấu hình tường lửa/ACL cần cân nhắc đặc tính từng giao thức.
## 5. Các giao thức mạng phổ biến
    1. HTTP (HyperText Transfer Protocol)

        Định nghĩa: Giao thức truyền tải siêu văn bản trên Internet.

        Chức năng: Cho phép trình duyệt và máy chủ web trao đổi dữ liệu (HTML, hình ảnh, video…).

        Port mặc định: 80
    2. DNS (Domain Name System)

        Định nghĩa: Hệ thống phân giải tên miền sang địa chỉ IP.

        Chức năng: Biến www.google.com → 142.250.190.78 để máy tính hiểu.

        Port mặc định: 53 (UDP/TCP)
    3. FTP (File Transfer Protocol)
        Định nghĩa: Giao thức truyền tải tập tin giữa máy khách và máy chủ.

        Chức năng: Cho phép upload/download file qua mạng.

        Port mặc định: 21 (control), 20 (data)
    4. SMTP (Simple Mail Transfer Protocol) 

        Định nghĩa: Giao thức gửi email giữa các máy chủ thư.

        Chức năng: Chuyển tiếp email từ người gửi đến người nhận.

        Port mặc định: 25
    5. DHCP (Dynamic Host Configuration Protocol)   

        Định nghĩa: Giao thức cấp phát địa chỉ IP tự động cho thiết bị trong mạng.

        Chức năng: Giúp thiết bị nhận IP, subnet mask, gateway, DNS mà không cần cấu hình thủ công.

        Port mặc định: 67 (server), 68 (client)
    6. SSH (Secure Shell)
        Định nghĩa: Giao thức kết nối từ xa an toàn qua mạng không an toàn.

        Chức năng: Quản lý máy chủ, thiết bị mạng từ xa với mã hóa dữ liệu.

        Port mặc định: 22
    7. Telnet
        Định nghĩa: Giao thức kết nối từ xa không mã hóa.

        Chức năng: Quản lý máy chủ, thiết bị mạng từ xa (ít dùng do không an toàn).

        Port mặc định: 23
    8. SNMP (Simple Network Management Protocol)
        Định nghĩa: Giao thức quản lý và giám sát thiết bị mạng.
        Chức năng: Thu thập thông tin, cấu hình thiết bị mạng từ xa.
        Port mặc định: 161 (agent), 162 (manager)
    9. ARP (Address Resolution Protocol)
        Định nghĩa: Giao thức phân giải địa chỉ IP sang địa chỉ MAC trong mạng LAN.
        Chức năng: Giúp thiết bị tìm địa chỉ MAC của thiết bị khác dựa trên địa chỉ IP.
        Hoạt động ở lớp liên kết dữ liệu (Data Link Layer).