# SSE-C
## Khái niệm
1. Khái niệm
- SSE-C cho phép bạn tự quản lý các khóa mã hóa của mình. Khi upload hoặc download dữ liệu, bạn phải gửi kèm khóa mã hóa trong yêu cầu HTTP. Hệ thống lưu trữ (như Ceph RGW) sẽ sử dụng khóa đó để thực hiện mã hóa/giải mã và sau đó tự hủy khóa khỏi bộ nhớ tạm, không lưu trữ khóa trong hệ thống.
2. Cách hoạt động 
- Quá trình Upload (PUT)
  - Client: Gửi đối tượng (Object) kèm theo khóa mã hóa (256-bit AES key) qua kết nối HTTPS bảo mật.
  - RGW: Nhận khóa từ header, thực hiện mã hóa dữ liệu.
  - Lưu trữ: Dữ liệu đã mã hóa được lưu vào OSD. RGW tính toán mã hash (salted HMAC) của khóa để đối chiếu sau này nhưng không lưu bản thân cái khóa đó.
  - Hủy khóa: RGW xóa khóa khỏi bộ nhớ sau khi hoàn tất.
- Quá trình Download (GET)
  - Client: Gửi yêu cầu lấy Object kèm đúng khóa đã dùng khi upload.
  - RGW: Kiểm tra mã hash của khóa gửi lên có khớp với metadata lưu kèm Object không.
  - Giải mã: Nếu khớp, RGW giải mã dữ liệu và trả về cho Client.
## Triển khai SSE-C
Bước 1: Tạo key mã hóa ngẫu nhiên 256 bits 
```sh
openssl rand 32 > sse.key # mỗi byte có 8 bits thì 32*8=256 bits
```
![](images_sse_s3/anh2.png)

Bước 2: Upload file
```sh
aws --endpoint-url http://192.168.1.138:8000 s3api put-object --bucket khiem.mmt1.test --key test-debug --body test.txt --sse-customer-algorithm AES256 --sse-customer-key fileb://sse.key ## không cần --sse-customer-key-md5 do khi dùng AWS CLI thì nó sẽ tự thêm header này vào request HTTP gửi cho RGW
```
![](images_sse_s3/anh21.png)

Bước 3: Tải file về cần file có đúng file chứa key khi upload
 - Khi upload file mà không có thêm key mã hóa, server sẽ trả về lỗi

![](images_sse_s3/anh22.png)

 - Upload file có thêm trường phương thức mã hóa và key đã tạo dùng để upload file cần tải xuống
```sh
aws --endpoint-url http://192.168.1.142:8000   s3api get-object   --bucket khiem.mmt.test   --key test-debug   --sse-customer-algorithm AES256   --sse-customer-key fileb://sse.key   output.txt
```
![](images_sse_s3/anh23.png)

***SSE-C không cấu hình vào hệ thống mặc định của Ceph nên ta vẫn có thể đọc và upload file 1 cách bình thường không cần mã hóa***
