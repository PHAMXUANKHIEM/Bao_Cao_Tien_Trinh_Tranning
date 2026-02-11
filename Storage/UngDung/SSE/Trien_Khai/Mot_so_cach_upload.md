# Rclone
## 1. Tổng quan 
- Rclone là một công cụ dòng lệnh mã nguồn mở, dùng để quản lý, đồng bộ hóa, sao lưu hoặc di chuyển dữ liệu giữa máy tính, máy chủ và hơn 70 dịch vụ lưu trữ đám mây phổ biến
- Rclone chỉ hỗ trợ mã hóa cho SSE-S3 và SSE-KMS, không hỗ trợ SSE-C

## 2. Cài đặt và cấu hình 
### Cài đặt rclone
```sh
sudo -v ; curl https://rclone.org/install.sh | sudo bash
```
### Cấu hình rclone
```sh
rclone config 
type = s3
provider = Ceph
env_auth = false
access_key_id = XXX
secret_access_key = YYY
region =
endpoint = https://ceph.endpoint.example.com
location_constraint =
acl =
server_side_encryption =
storage_class =
```
***Cấu hình cho SSE-KMS***

![](images_sse_s3/anh38.png)

***Cấu hình cho SSE-S3***

![](images_sse_s3/anh39.png)

### Upload 
```sh
# SSE-S3
rclone copy test.txt Ceph-SSE-S3:khiem.mmt204.test/   --s3-region us-east-zg-1   --s3-location-constraint us-east-zg-1   --s3-server-side-encryption AES256   -P
```
![](images_sse_s3/anh43.png)

```sh
# SSE-KMS
rclone  copy test-sse-kms.txt Ceph-SSE-KMS:khiem.mmt204.test/kms
```
![](images_sse_s3/anh44.png)

# MinIO Client
## 1. Tổng quan
- MinIO Client là một trong những công cụ quản lý S3 phổ biến trên giao diện dòng lệnh. Hỗ trợ người dùng đã dạng thao tác thuận tiện hơn các bucket, object cũng như các tính năng khác trong S3.
- MinIO Client hỗ trợ mã hóa cho SSE-S3, SSE-KMS, SSE-C
## 2. Cài đặt và cấu hình
### Cài đặt MinIO Client 
```sh
curl -O https://dl.min.io/client/mc/release/linux-amd64/mc
chmod +x mc
mv mc /usr/local/bin/
```
### Cấu hình MinIO Client
- Cấu hình alias, endpoint, access-key và secret-key
```sh
mc alias set <ALIAS> <YOUR-S3-ENDPOINT> <YOUR-ACCESS-KEY> <YOUR-SECRET-KEY>
```
![](images_sse_s3/anh45.png)
### Cấu hình upload bằng mã hóa SSE-KMS
```sh
mc encrypt set sse-kms ceph-bucket-key Ceph-SSE-KMS/khiem.mmt204.test
mc cp test2.txt Ceph-SSE-KMS/khiem.mmt204.test/hihi
mc stat Ceph-SSE-KMS/khiem.mmt204.test/hihi
```

![](images_sse_s3/anh46.png)

### Cấu hình upload bằng mã hóa SSE-S3
```sh
mc encrypt set sse-s3 Ceph-SSE-KMS/khiem.mmt204.test
mc cp test-sse-s3.txt Ceph-SSE-KMS/khiem.mmt204.test/sse-s3
mc stat Ceph-SSE-KMS/khiem.mmt204.test/sse-s3
```
![](images_sse_s3/anh47.png)

### Cấu hình upload bằng mã hóa SSE-C
***LƯU Ý: Chỉ dùng được SSE-C khi có chứng chỉ https***
- MinIO ko hỗ trợ set SSE-C mà phải cấu hình mặc định
- Tạo một khóa ngẫu nhiên dạng Base64
```sh
openssl rand -base64 32
```
- Gán khóa cho một Bucket cụ thể
```sh
export MC_ENCRYPT_KEY="myminio/my-bucket=7u5v...v8A="
```
- Upload file bình thường sẽ tự áp dụng SSE-C
### Xóa cấu hình 
```sh
mc encrypt clear myaistor/mydata
```
## Upload bằng Python 
### SSE-S3
```sh
import boto3
s3_client = boto3.client(
    's3',
    endpoint_url='http://192.168.1.142:8000',
    aws_access_key_id='4Z0I11STI5YXIHC4PCX2',
    aws_secret_access_key='mLaKyEA6t9YzzqaMRwLpZXLnQ4IOyYMrOx4z21fa',
    region_name='us-east-1'
)
def upload_with_sse_s3(bucket, key, data):
    response = s3_client.put_object(
        Bucket=bucket,
        Key=key,
        Body=data,
        ServerSideEncryption= 'AES256'
    )
    return response
upload_with_sse_s3('khiem.mmt.test', 'test.txt', 'Nội dung bảo mật')
```
### SSE-KMS
```sh
import boto3
s3_client = boto3.client(
    's3',
    endpoint_url='http://10.2.1.54:8000',
    aws_access_key_id='EADBJIHZ3INBHZ9S73WA',
    aws_secret_access_key='45H2flJh9yy8bJSlhm02WAwWWXRpWivwCodritLv',
    region_name='us-east-1'
)
def upload_with_sse_s3(bucket, key, data):
    response = s3_client.put_object(
        Bucket=bucket,
        Key=key,
        Body=data,
        ServerSideEncryption= 'aws:kms',
        SSEKMSKeyId='ceph-bucket-key'
    )
    return response
upload_with_sse_s3('khiem.mmt2004.test', 'test1.txt', 'Nội dung bảo mật')
```