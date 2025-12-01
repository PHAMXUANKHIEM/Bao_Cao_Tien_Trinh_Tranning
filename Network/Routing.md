# Routing Tĩnh (Static Routing)
## 1. Định nghĩa Static Route

- Static Route là một tuyến đường được cấu hình thủ công trên router để chỉ định cách để router chuyển tiếp gói tin tới một mạng đích.
- Không thay đổi tự động; admin phải tự cập nhật nếu có thay đổi mạng.
- Ngược lại với Dynamic Routing (OSPF, RIP, EIGRP, BGP…).


## 2. Cấu trúc cơ bản của Static Route

Cú pháp trên Cisco IOS:

```sh
ip route [DESTINATION_NETWORK] [SUBNET_MASK] [NEXT_HOP_IP | EXIT_INTERFACE] [ADMIN_DISTANCE]

```

- `DESTINATION_NETWORK`: mạng đích bạn muốn đến.
- `SUBNET_MASK`: subnet mask của mạng đích.
- `NEXT_HOP_IP`: IP của router kế tiếp.
- `EXIT_INTERFACE`: interface vật lý trên router để đi tới mạng đích.
- `ADMIN_DISTANCE` (tùy chọn): độ ưu tiên của route (mặc định 1).

## 3. Các loại Static Route

      1. Standard Static Route
         - Route thông thường, chỉ định rõ mạng đích và next-hop.
         - Ví dụ như ở trên.
      2. Default Static Route
         - Dùng khi muốn router gửi tất cả gói tin không khớp route nào vào một đường đi duy nhất.
         - Cú pháp:
            
            ```sh
            ip route 0.0.0.0 0.0.0.0 [NEXT_HOP_IP | EXIT_INTERFACE]
            
            ```
      3. Floating Static Route
         - Static route dự phòng khi route chính (dynamic hoặc static khác) bị mất.
         - Sử dụng Administrative Distance lớn hơn route bình thường.
         - Ví dụ:
            
            ```sh
            ip route 192.168.2.0 255.255.255.0 192.168.1.2 200
            
            ```
            
      4. Host Route
         - Dùng để định tuyến tới một IP cụ thể, subnet mask 255.255.255.255.
         - Ví dụ:
            
            ```sh
            ip route 192.168.2.10 255.255.255.255 192.168.1.2
            
            ```
        
      5. Static Route qua Interface
         - Thay vì next-hop IP, chỉ định trực tiếp interface.
         - Ví dụ:
            
            ```sh
            ip route 192.168.3.0 255.255.255.0 FastEthernet0/0
            
            ```

## 4. Kiểm tra và quản lý Static Route

      1. Xem bảng định tuyến

      ```sh
         show ip route

      ```

      - Các static route thường có chữ `S` đứng trước.
      1. Xóa static route

         ```sh
         no ip route [DESTINATION_NETWORK] [SUBNET_MASK] [NEXT_HOP_IP | EXIT_INTERFACE]

         ```

         1. Thử ping tới mạng đích

         ```sh
         ping 192.168.2.1

         ```

         - Đảm bảo route hoạt động đúng.