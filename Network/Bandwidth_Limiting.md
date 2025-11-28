TC
1. Khai niệm Bandwidth Limiting
- Bandwidth Limiting (Giới hạn băng thông) là kỹ thuật kiểm soát lưu lượng mạng để đảm bảo rằng các ứng dụng và dịch vụ quan trọng có đủ băng thông hoạt động hiệu quả.
- Mục đích của Bandwidth Limiting bao gồm:
  - Ngăn chặn việc sử dụng băng thông quá mức bởi các ứng dụng không quan trọng.
  - Đảm bảo chất lượng dịch vụ (QoS) cho các ứng dụng quan trọng như VoIP, video conferencing.
  - Quản lý lưu lượng mạng để tránh tắc nghẽn và cải thiện hiệu suất mạng.
2. Các phương pháp Bandwidth Limiting
- Traffic Shaping: Điều chỉnh lưu lượng mạng bằng cách trì hoãn các gói tin không quan trọng để ưu tiên các gói tin quan trọng hơn.
- Rate Limiting: Giới hạn tốc độ truyền dữ liệu cho một ứng dụng hoặc dịch vụ cụ thể.
- Policing: Loại bỏ các gói tin vượt quá giới hạn băng thông đã định sẵn.
3. TC trên Linux
- TC (Traffic Control) là công cụ dòng lệnh trên Linux dùng để quản lý và điều khiển lưu lượng mạng.
- Các thành phần chính của TC:
  - Queues: Hàng đợi lưu trữ các gói tin chờ xử lý.
  - Classes: Lớp phân loại lưu lượng để áp dụng các chính sách khác nhau.
  - Filters: Bộ lọc để xác định lưu lượng nào sẽ được áp dụng chính sách.
- Cú pháp cơ bản của TC:
```
tc [ OPTIONS ] OBJECT { COMMAND | help }
```
