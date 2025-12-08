# Mount
## 1. Khái niệm
- Là một lệnh cơ bản trên Linux cho phép gắn hệ thống têp tin từ bên ngoài (USB,...) vào 1 tệp trong Linux để có thể truy cập vào hệ thống tệp tin từ bên ngoài đó
## 2. Cách dùng
1. Cú pháp: 
```sh
mount [option] [thiết_bị] [điểm gắn kết]
```
Ví dụ khi cắm usb:
```sh
mount /dev/sdb1 /home/usb 
```
Ta có thể truy cập usb qua thư mục `/home/usb`
### Option:
          
                            |        Tên lệnh          |       Công dụng         |
                            |          -l              |Liệt kê mọi filesystem   |
                            |                          |đã được mount            |
                            |                          |                         |
                            |          -h              |Hiển thị các option của  |
                            |                          |lệnh                     |
                            |                          |                         |
                            |          -v              |Hiển thị thông tin của   |
                            |                          |phiên bản                |
                            |                          |                         |
                            |          -a              |Mount mọi thiết bị trong |
                            |                          |/etc/fstab               |  
                            |                          |                         |
                            |          -t              |Loại filesystem nào được |
                            |                          |sử dụng                  |
                            |                          |                         |
                            |          -T              |Mô tả file fstab bị thay |
                            |                          |thế                      |
                            |                          |                         |
                            |          -r              |mount ở chế độ chỉ đọc   |
                            |                          |                         |

# Unmount
- Dùng để ngắt kết nối tới hệ thống tệp tin hoặc dùng khi check fsck. Khi rút usb chạy lệnh:
```sh 
unmount /dev/sdb1 /home/usb
```