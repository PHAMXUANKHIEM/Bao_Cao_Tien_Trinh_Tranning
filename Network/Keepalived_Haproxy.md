## I. Keepalived + HAProxy 
#  1. Khai niệm
- Keepalived là một phần mềm mã nguồn mở dùng để cung cấp tính năng High Availability (HA) cho các dịch vụ mạng, đặc biệt là trong môi trường Linux. Nó thường được sử dụng kết hợp với HAProxy để đảm bảo rằng các dịch vụ web hoặc ứng dụng luôn sẵn sàng và có thể chịu lỗi.
- HAProxy là một phần mềm cân bằng tải (load balancer) mã nguồn mở, được thiết kế để phân phối lưu lượng mạng đến nhiều máy chủ backend nhằm tối ưu hiệu suất và độ tin cậy của ứng dụng.
#  2. Cách hoạt động
- Keepalived sử dụng giao thức VRRP (Virtual Router Redundancy Protocol) để tạo ra một địa chỉ IP ảo (VIP - Virtual IP) mà các máy chủ trong cụm có thể chia sẻ. Khi một máy chủ chính (master) gặp sự cố, Keepalived sẽ tự động chuyển quyền điều khiển VIP sang máy chủ dự phòng (backup), đảm bảo rằng dịch vụ vẫn tiếp tục hoạt động mà không bị gián đoạn.
- HAProxy sẽ lắng nghe trên VIP và phân phối lưu lượng đến các máy chủ backend dựa trên các thuật toán cân bằng tải như round-robin, least connections, v.v. Khi một máy chủ backend không phản hồi, HAProxy sẽ tự động loại bỏ nó khỏi danh sách phân phối lưu lượng cho đến khi nó trở lại hoạt động.
#  3. Cấu hình cơ bản
- Ta sẽ cấu hình Keepalived và HAProxy trên hai máy chủ Linux để thiết lập một hệ thống cân bằng tải với tính năng High Availability.
- Giả sử ta có hai máy chủ web backend với địa chỉ IP là 10.40.3.201 va 10.40.3.17
- Cài đặt Keepalived và HAProxy trên các máy chủ Linux.
```sh
   sudo -i
   apt install keepalived haproxy -y
```
- Cấu hình HAProxy để thiết lập các backend server và các quy tắc cân bằng tải.
```sh
  /etc/haproxy/haproxy.cfg
```
- Ví dụ cấu hình HAProxy:
```sh
      global
      log /dev/log    local0
      maxconn 4096
      daemon

      defaults
      log     global
      mode    http
      retries 3
      timeout connect 5s
      timeout client  50s
      timeout server  50s

      frontend http_frontend
      bind *:80
      default_backend http_backend

      backend http_backend
      balance roundrobin
      option httpchk GET /
      server web1 10.40.3.201:80 check
      server web2 10.40.3.17:80 check
```
- Cấu hình Keepalived để thiết lập VIP và các tham số VRRP.
  /etc/keepalived/keepalived.conf
- Ví dụ cấu hình Keepalived:
```sh
    global_defs {
    router_id LVS_DEVEL
    enable_script_security
    }
    vrrp_script check_haproxy {
    script "/etc/keepalived/check_haproxy.sh"
    fall 3
    rise 2
    weight -20
    user root
    }

    vrrp_instance VI_1 {
    state MASTER
    interface ens3
    virtual_router_id 51
    priority 110
    advert_int 1
    authentication {
        auth_type PASS
        auth_pass 123456
    }

    virtual_ipaddress {
        192.168.1.100/24
    }
    track_script {
        check_haproxy
    }
    }
```
- Tạo script kiểm tra trạng thái của HAProxy.
  /etc/keepalived/check_haproxy.sh
```sh
    #!/bin/bash

    LOG_FILE="/var/log/haproxy.log"

    LAST_LINES=20

    if tail -n $LAST_LINES $LOG_FILE | grep -q -E "Connection refused|143|unable to connect"; then

    exit 1

    else

    exit 0

    fi
  ```
- Cấp quyền thực thi cho script.
```sh
   chmod +x /etc/keepalived/check_haproxy.sh
```
- Khởi động và kích hoạt dịch vụ Keepalived và HAProxy.
```sh
   systemctl start keepalived haproxy
   systemctl enable keepalived haproxy
```   
4. Kiểm tra và giám sát
- Kiểm tra trạng thái của dịch vụ Keepalived và HAProxy.
```sh
   systemctl status keepalived haproxy
```
- Sử dụng lệnh `ip addr` để xác nhận rằng VIP đã được gán đúng trên máy chủ chính.
- Kiểm tra cân bằng tải bằng cách truy cập VIP từ trình duyệt web hoặc sử dụng công cụ như `curl` để gửi yêu cầu HTTP và xác nhận rằng lưu lượng được phân phối đều đến các máy chủ backend.
- Giám sát log của HAProxy để theo dõi hiệu suất và các lỗi có thể xảy ra.
```sh
   tail -f /var/log/haproxy.log
``` 