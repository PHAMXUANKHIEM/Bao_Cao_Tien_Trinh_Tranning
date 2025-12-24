# SYSTEMCALL
## Khái niệm 
- System call là cơ chế cơ bản cho phép một chương trình (đang chạy ở chế độ người dùng- user mode) yêu cầu dịch vụ từ nhân của hệ điều hành. Nó là cầu nối giữa phần mềm ứng dụng và phần cứng máy tính
## Các vùng nhớ
- Để đảm bảo và an toàn, trong Linux chia ra làm 2 vùng chính:
  - User space (Không gian người dùng): Là nơi các ứng dụng bình thường chạy và bị giới hạn quyền sử dụng tài nguyên phần cứng
  - Kernal space (Không gian nhân): Là nơi hệ điều hành chạy có quyền kiểm soát hoàn toàn về phần cứng và tài nguyên
- Một ứng dụng muốn ghi dữ liệu vào phần cứng qua mạng thì không tự mình làm được mà phải nhờ System Call để nhờ Kernal làm hộ
## Cách hoạt động của System Call
1. Yêu cầu: Chương trình sẽ gọi một hàm thư viện (`open()` trong Python hoặc `printf()` trong C)
2. Kích hoạt (Trigger): Thư viện này sẽ gọi System Call tương ứng. Khi đó một lệnh ngắt mềm (software interrput) hoặc lệnh đặc biệt (`syscall` trong assembly x84-64) được thực thi
3. Chuyển chế độ: Khi lệnh thực thi thì CPU sẽ chuyển chế độ từ User Mode sang Kernal Mode
4. Thực thi: Kernal kiểm tra quyền hạn, thực hiện yêu cầu 
5. Trả về : Kernal trả kết quả về cho chương trình và CPU chuyển về  chế độ User Mode
## Phân loại System call trên Linux
1. Quản lý tiến trình (Process Control)
  - `fork()`: Tạo một tiến trình mới 
  - `exec()`: Thực thi một chương trình mới
  - `exit()`: Chấm dứt tiến trình
  - `wait()`: Chờ tiến trình con kết thúc
2. Quản lý file 
  - `open()`: Mở file
  - `read()`: Đọc dữ liệu từ file vào bộ đệm
  - `write()`: Ghi dữ liệu từ file vào bộ nhớ đệm
  - `close()`: Đóng file
3. Quản lý thiết bị và thông tin
  - `ioctl`: Kiểm soát thiết bị (Input/Output/Control)
  - `getPID`: Lấy PID của tiến trình 
4. Giao tiếp mạng
  - `socket`: Tạo một điểm cuối để giao tiếp mạng
  - `bind()`: Gán địa chỉ IP/PORT cho socket
  - `listen()`: Lắng nghe kết nối đến 
  - `connect()`: Kết nối tới máy chủ từ xa
    