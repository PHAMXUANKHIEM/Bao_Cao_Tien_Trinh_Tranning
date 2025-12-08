# Mount
## 1. Khái niệm
- Là một lệnh cơ bản trên Linux cho phép gắn hệ thống têp tin từ bên ngoài (USB,...) vào 1 tệp trong Linux để có thể truy cập vào hệ thống tệp tin từ bên ngoài đó
## 2. Cách dùng
1. Cú pháp: 
```sh
mount [option] [thiết_bị] [điểm gắn kết]
```
-Option: 
                      |        Tên lệnh          |       Công dụng        |
                      |          -l              |Liệt kê mọi filesystem  |
                      |                          |đã được mount           |
                      |                          |                        |
                      |          -h              |Hiển thị các option của |
                      |                          |lệnh                    |
                      |                          |                        |
                      |          -v              |Hiển thị thông tin của  |
                      |                          |phiên bản               |
                      |                          |                        |
                      |          -a              |Mount mọi thiết bị trong|
                      |                          |/etc/fstab              |  ### fstab là nơi cấu hình mount trong Linux khi khởi động
                      |                          |                        |
                      |          -t              |Loại filesystem nào được|
                      |                          |sử dụng                 |
                      |                          |                        |
                      |          -T              |Mô tả file fstab bị thay|
                      |                          |thế                     |
                      |                          |                        |
                      |          -r              |mount ở chế độ chỉ đọc  |
                      |                          |                        |

