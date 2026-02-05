# Một số kịch bản test 
Kịch bản: 
1. Chưa config sse. Sử dụng s3 upload bình thường nhiều file vào(1k file), read xem bình thường
- Đã có folder 1k file
- Upload lên S3 bình thường (dùng sync để ổn định hơn với thư mục nặng) 
```sh
aws --endpoint-url http://192.168.1.97:8000 s3 sync my_data/ s3://khiem.mmt204.test/ 
```
![](images_test_case/anh1.png)

- Đọc các file đã tải 
```sh
aws --endpoint-url http://192.168.1.97:8000 s3 cp s3://khiem.mmt204.test/file_500.txt -
```

![](images_test_case/anh2.png)

2. Do muốn sử dụng sse vào các file, dù đã cấu hình các dịch vụ SSE-S3 hay SSE-KMS nếu khi upload file mà không có các trường `--sse AES256` (kích hoạt SSE-S3) hay `--sse aws:kms` (kích hoạt KMS) thì mặc định file sẽ upload theo cách bình thường như trên phần 1

3. Khi đã cấu hình SSE-S3 và SSE-KMS ta vẫn có thể đọc được các file upload bình thường như trên phần 1 


