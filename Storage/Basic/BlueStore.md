# Bluestore
## Khái niệm
- BlueStore là storage backend mặc định của Ceph, được thiết kế để thay thế FileStore (backend cũ). Thay vì phải sử dụng XFS hoặc EXT4 làm hệ thống tập tin trung gian, BlueStore ghi dữ liệu trực tiếp lên thiết bị lưu trữ (như ổ cứng HDD, SSD).

![](images_filestore/anh1.png)
## Kiến trúc của BlueStore
- BlueStore bao gồm các thành phần chính sau:
1. **BlueFS**: Là hệ thống tập tin nội bộ của BlueStore, được sử dụng để lưu trữ metadata và các cấu trúc dữ liệu cần thiết cho hoạt động của BlueStore.
2. **RocksDB**: để lưu trữ metadata của đối tượng (object metadata) và các thông tin khác liên quan đến dữ liệu nhờ đó có thể truy cập nhanh chóng và hiệu quả.
3. **RAW DATA**: Là nơi lưu trữ dữ liệu thực tế của các đối tượng (objects) được lưu trữ trong Ceph.
## Điểm vượt trội
1. Loại bỏ ghi đúp
- Trong FileStore ta phải ghi 2 lần: 1 lần vào Journal và 1 lần vào hệ thống file chính. Còn với BlueStore ta chỉ cần ghi 1 lần trực tiếp vào ổ cứng, sau đó sẽ cập nhật metadata vào RocksDB. Điều này giúp cải thiện hiệu suất ghi dữ liệu tổng thể của hệ thống lưu trữ.
2. CoW (Copy on Write)
- BlueStore hỗ trợ CoW, cho phép tạo các bản sao của dữ liệu mà không cần sao chép toàn bộ dữ liệu.
- Thay vì ghi đè trực tiếp lên dữ liệu cũ, BlueStore sẽ ghi dữ liệu mới vào một vị trí khác trên ổ cứng và cập nhật metadata để trỏ đến vị trí mới này.
3. Checksum
- BlueStore sử dụng checksum để đảm bảo tính toàn vẹn của dữ liệu. Mỗi khi dữ liệu được ghi vào BlueStore, một giá trị checksum sẽ được tính toán và lưu trữ cùng với dữ liệu. Mỗi lần đọc lên dữ liệu, BlueStore sẽ kiểm tra lại checksum để đảm bảo rằng dữ liệu không bị hỏng hoặc thay đổi.
4. Compression (Nén dữ liệu)
- BlueStore hỗ trợ nén dữ liệu để giảm dung lượng lưu trữ và cải thiện hiệu suất truyền tải dữ liệu. Khi dữ liệu được ghi vào BlueStore, nó có thể được nén trước khi lưu trữ trên ổ cứng. Khi dữ liệu được đọc lên, nó sẽ được giải nén tự động.
5. Tiering (Phân lớp lưu trữ)
- BlueStore hỗ trợ phân lớp lưu trữ, cho phép dữ liệu được lưu trữ trên các loại thiết bị lưu trữ khác nhau dựa trên tần suất truy cập và yêu cầu hiệu suất. Ví dụ, dữ liệu nặng để ở ổ HDD, metadata nhẹ để ở ổ SSD.
## So sánh BlueStore và FileStore
| Đặc điểm         | BlueStore                         | FileStore                            |
|------------------|-----------------------------------|----------------------------------    |
|Hệ thống tập tin  | Không sử dụng hệ thống tập tin    | Sử dụng hệ thống tập tin (XFS, EXT4) |
|Hiệu suất ghi     | Cao hơn do ghi trực tiếp lên ổ    | Thấp hơn do ghi 2 lần (Journal + hệ  |
|                  |cứng                               |thống tập tin)                        |
|Quản lý metadata  | Sử dụng RocksDB                   |Sử dụng XATTRs và file riêng biệt     |
|Tính toàn vẹn data| Sử dụng checksum                  | Không có checksum                    |
|Hỗ trợ CoW        | Hỗ trợ                            | Không hỗ trợ                         |
|Nén dữ liệu       | Hỗ trợ                            | Không hỗ trợ                         |
|Phân lớp lưu trữ  | Hỗ trợ                            | Không hỗ trợ                         |
