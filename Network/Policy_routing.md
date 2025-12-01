# Policy Routing

## 1. Khái niệm
- Policy Routing (Định tuyến theo chính sách) là kỹ thuật định tuyến lưu lượng mạng dựa trên các chính sách hoặc tiêu chí cụ thể thay vì chỉ dựa vào địa chỉ đích.
- Mục đích của Policy Routing bao gồm:
  - Tối ưu hóa hiệu suất mạng bằng cách phân phối lưu lượng theo các yêu cầu khác nhau.
  - Cải thiện bảo mật bằng cách kiểm soát luồng dữ liệu dựa trên các chính sách.
  - Hỗ trợ các dịch vụ đa dạng như VoIP, video streaming, và ứng dụng doanh nghiệp với các yêu cầu băng thông khác nhau.
- Policy Routing thường được sử dụng trong các môi trường mạng phức tạp, nơi có nhiều loại lưu lượng và yêu cầu khác nhau.
- Khác với Static Routing:
- Cho phép định tuyến dựa trên nhiều tiêu chí như địa chỉ nguồn, giao thức, cổng nguồn, v.v.
- Linh hoạt hơn trong việc quản lý lưu lượng mạng.
- Có thể kết hợp với các kỹ thuật khác như QoS để tối ưu hóa hiệu suất mạng.
- Thường được triển khai trên các router và thiết bị định tuyến cao cấp.
- Ngược lại với Static Routing (chỉ dựa vào địa chỉ đích).
- Cách hoạt động của Policy Routing
  - Policy Routing sử dụng các bảng định tuyến bổ sung (Policy Routing Table) để xác định cách xử lý lưu lượng dựa trên các chính sách đã định nghĩa.
  - Khi một gói tin đến router, thiết bị sẽ kiểm tra các tiêu chí trong chính sách định tuyến (như địa chỉ nguồn, giao thức, cổng nguồn) và so sánh với các quy tắc trong bảng định tuyến chính sách.

## 2. Cách dùng (ip route / ip rule)
- Thêm bảng route:
```bash
ip route add default via 10.0.0.1 dev eth0 table 100
```
- Thêm rule:
```bash
ip rule add from 192.168.1.0/24 table 100
```
## 3. Ứng dụng
- Multi‑WAN, policy cho từng tenant, route theo mark từ iptables.
 bảng định tuyến bổ sung (Policy Routing Table) để xác định cách xử lý lưu lượng dựa trên các chính sách đã định nghĩa.
- Khi một gói tin đến router, thiết bị sẽ kiểm tra các tiêu chí trong chính sách định tuyến (như địa chỉ nguồn, giao thức, cổng nguồn) và so sánh với các quy tắc trong bảng định tuyến chính sách.
- Nếu có một quy tắc phù hợp, router sẽ sử dụng thông tin trong quy tắc đó để quyết định cách định tuyến gói tin.
- Nếu không có quy tắc phù hợp, router sẽ sử dụng bảng định tuyến chính (Main Routing Table) để xử lý gói tin như bình thường.
