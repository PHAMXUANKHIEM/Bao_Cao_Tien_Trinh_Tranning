# Bucket Logging

## Khái niệm

- Là cơ chế ghi lại toàn bộ lich sử truy cập và thao tác trên một bucket nguồn 

- Các bản ghi này được đóng gói và lưu trữ dưới dạng object bên trong 1 bucket riêng biệt gọi là Log Bucket

- Chỉ được áp dụng cho phiên bản v20.2.0 Tentacle
## Các quy tắc đối bắt buộc đối với Log Bucket

- Để làm nơi chứa log nó phải tuân thủ các điều kiện sau:

  - Phải được tạo trước khi bật tính năng ghi log cho bucket nguồn

  - Không được là chính bucket nguồn

  - Không được bật tính năng mã hóa, logging, nén hoặc RequestPayer trên Log Bucket này

  - Phải nằm cùng 1 Zonegroup với bucket nguồn

  - Có thể thuộc về nhiều tài khoản khác nhau nếu phân Bucket Policy hợp lý

## Độ tin cậy và cơ chế đồng bộ

- Đê đảm bảo hiệu suất, hệ thống không ghi trực tiếp log và Log Bucket

- Mặc định log chỉ được đẩy vào Log Bucket sau mỗi 5 phút hoặc file log đạt 128 MB dung lượng

- Trong khoảng thời gian chờ, file log sẽ được ghi ở vùng lưu trữ tạm, ta có thể dùng lệnh sau để ép nó ghi trực tiếp luôn vào Log Bucket

```sh
radosgw-admin bucket logging flush --bucket <ten_bucket>
```

## Các chế độ hoạt động

- Standard (Mặc định): Hệ thống sẽ ghi log sau khi thao tác người dùng đã hoàn tất. Nếu việc ghi log bị lỗi, các thao tác người dùng vẫn hoàn tất thành công bình thường. Định dạnh log sẽ theo chuẩn S3

- Journal: Hệ thống sẽ ghi log trước khi người dùng hoàn tất. Nếu việc ghi log thất bại, thao tác của người dùng sẽ bị lỗi ngay lập tức. Định dạng log sẽ đơn giản theo chuẩn riêng của Ceph

## Phân quyền và hạn mức

- Policy: Bucket Policy của Log Bucket phải cho phép hành động `s3:PutObject` được thực hiện bởi một chủ đề dịch vụ đặc biệt là `logging.s3.amazonaws.com`

- Quota: Hạn mức dung lượng (Quota) vẫn áp dụng bình thường trên Log Bucket. Nếu ở chế độ Journal Quota đầy, mọi thao tác trên bucket nguồn sẽ bị lỗi theo. Còn nếu ở chế độ Standard, các thao tác trên bucket nguồn vẫn hoạt động nhưng sẽ bỏ qua việc ghi log

## Triển khai 

1. Tạo 2 bucket mới 

```sh
# Tạo log bucket

aws s3 mb --endpoint http://10.2.6.128:8000 s3://log.bucket.test --region us-east-zg-1

# Tạo bucket nguồn

aws s3 mb --endpoint http://10.2.6.128:8000 s3://bucket.source.test --region us-east-zg-1

```

2. Tạo policy áp dụng cho log bucket

```sh
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Sid": "AllowLoggingFromSourceBucket",
      "Effect": "Allow",
      "Principal": {
        "Service": "logging.s3.amazonaws.com"
      },
      "Action": "s3:PutObject",
      "Resource": "arn:aws:s3:::log.bucket.test/*",
      "Condition": {
        "ArnLike": {
          "aws:SourceArn": "arn:aws:s3:::khiem.mmt204.test"
        }
      }
    }
  ]
}
```
3. Áp dụng policy cho log bucket

```sh

aws --endpoint-url http://10.2.6.128:8000 s3api put-bucket-policy --bucket log.bucket.test --policy file://log-policy.json 

```

4. Bật Logging trên Bucket nguồn 

- Tạo file cấu hình enable_logging.json

```sh

{
  "LoggingEnabled": {
    "TargetBucket": "log.bucket.test",
    "TargetPrefix": "logs/khiem-mmt204/"
  }
}
```

5. Áp dụng cho Bucket nguồn 

```sh

aws --endpoint-url http://192.168.1.88:8000 s3api put-bucket-logging     --bucket khiem.mmt204.test     --bucket-logging-status file://enable_logging.json 

```

6. Check xem bucket đã được được bật bucket logging chưa

```sh
aws --endpoint-url http://192.168.1.88:8000 s3api get-bucket-logging --bucket khiem.mmt204.test
```

![](images_RADOS/anh88.png)

7. Áp dụng xả log xuống ngay lập tức

- Do mặc định log chỉ được đẩy vào Log Bucket sau mỗi 5 phút hoặc file log đạt 128 MB dung lượng nên ta cần áp dụng lệnh xả log ngay lập tức vào bucket chứa log

```sh
radosgw-admin bucket logging flush --bucket khiem.mmt204.test
```

![](images_RADOS/anh89.png)

8. Check bucket ghi log đã có log chưa  

```sh
aws --endpoint-url http://192.168.1.88:8000 s3 ls s3://log.bucket.test/ --recursive
```

![](images_RADOS/anh90.png)


9. Tải xuống và xem log

```sh

aws --endpoint-url http://192.168.1.88:8000 s3 cp s3://log.bucket.test/logs/khiem-mmt204/2026-03-16-07-25-37-00000000008QF3NO check.txt
```

![](images_RADOS/anh91.png)

10. Ta có thể triển khai cho bucket này bucket lifecycle để tự động xóa các file log 