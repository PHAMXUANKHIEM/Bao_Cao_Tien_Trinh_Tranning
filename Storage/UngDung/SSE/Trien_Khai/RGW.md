# Radosgateway
## Khái niệm 
- Là một giao diện lưu trữ đối tượng đóng vai trò là cầu nối để các ứng dụng giao tiếp vào bên trong cụm
- Là một web server giúp chuyển đổi các yêu cầu HTTP thành lệnh để chuyển xuống RADOS. Nó không hiện ra như thư mục mà có giao diện hỗ trợ AWS S3 và Swift mà giao tiếp trực tiếp qua API

![](images_RADOS/anh11.png)
## Chức năng chính 

## Ứng dụng
- Ứng dụng có thể bypass qua RADOS gateway và truy xuất trực tiếp tới librados, thường thấy trong các ứng dụng doanh nghiệp đòi hỏi hiệu năng cao. Ceph cho phép truy xuất trực tiếp tới cluster, điều khác biệt so với các hệ thống lưu trữ khác vốn giới hạn về các interface giao tiếp.

![](images_RADOS/anh12.png)
## Tạo RGW trên Cephadm
Bước 1: Tạo user cho bucket và lấy access_key và secret_key
 - Tạo tài khoản, xem access_key và secret_key:
```sh
radosgw-admin user create --uid=admin --display-name="Tài khoản admin"
```
![](images_sse_s3/anh3.png)

 - Lưu thông tin của access_key và secret_ket
 - Nếu quên ta có thể  lấy `access_key` và `secret_key`:
  - Liệt kê user:
```sh 
  radosgw-admin user list
  ```
  - Xem chi tiết từng user và lấy `access_key`, `secret_key`
```sh
  rgwosgw-admin user info --uid=admin
  ```
Bước 2: Khởi động và tạo dịch vụ RGW của Ceph
 - Enable service rgw
```sh
ceph mgr module enable rgw
```
 - Tạo tên miền, vùng
```sh
ceph orch apply rgw sse --realm=myorg --zonegroup=us-east-zg-1 --zone=us-east-1 --placement="3 ceph1 ceph2 ceph3" --port=8000
```
Bước 3: Cài đặt, configure aws-cli để config bucket
** Lưu ý cài bản aws-cli v2 trở lên trong môi trường python3.9 trở lên để hỗ trợ đầy đủ thư viện boto3
- Cài đặt aws-cli
```sh
sudo yum remove awscli
curl "https://awscli.amazonaws.com/awscli-exe-linux-x86_64.zip" -o "awscliv2.zip"
unzip awscliv2.zip
sudo ./aws/install
aws --version
```
![](images_sse_s3/anh4.png)
- Configure aws-cli (Điền access_key và secret_key như trên đã lưu lại)
```sh
aws configure
```
![](images_sse_s3/anh5.png)

- Cài đặt 
Bước 4: Tạo bucket với aws-cli tại endpoint cụ thể: 
```sh
aws --endpoint-url http://10.2.1.54:8000 s3api create-bucket --bucket khiem.mmt204.test --region us-east-1
aws s3 mb --endpoint http://10.2.1.54:8000 s3://khiem.mmt204.test --region us-east-1 
```
![](images_sse_s3/anh6.png)

Bước 5: Tạo policy để bucket có thể truy cập public
```sh
vi public.json
{
  "Version":"2012-10-17",
  "Statement":[{
    "Sid":"PublicRead",
    "Effect":"Allow",
    "Principal":"*",
    "Action":["s3:GetObject","s3:ListBucket"],
    "Resource":[
      "arn:aws:s3:::khiem.mmt204.test",
      "arn:aws:s3:::khiem.mmt204.test/*"
    ]
  }]
}

```
Bước 6: Áp dụng policy cho bucket
```sh
aws   --endpoint-url http://10.2.6.110:8000   s3api put-bucket-policy   --bucket khiem.mmt204.test  --policy file://public-bucket.json
```
Bước 5: Tạo, put, get file vừa tạo qua dịch vụ S3
- Put dữ liệu lên
```sh
echo "hihi" >> test.txt
aws --endpoint http://10.2.6.110:8000 s3 cp test.txt s3://khiem.mmt204.test/test
aws s3api head-object --bucket khiem.mmt204.test --key test.txt --endpoint-url http://10.2.6.110:8000
 ```
![](images_sse_s3/anh7.png)
- GET dữ liệu về: 
```sh
aws s3 cp s3://khiem.mmt204.test/test test.txt --endpoint-url http://10.2.6.110:8000
```
![](images_sse_s3/anh8.png)

## Tạo RGW trên Ceph-deploy
 Bước 1: Khởi tạo RGW bằng ceph-deploy
 ```sh
 ceph-deploy rgw create host-192-168-1-106 # Mặc định chạy trên port 7480
 ```
 Bước 2: Tạo user cho bucket và lấy access_key và secret_key
 - Tạo tài khoản, xem access_key và secret_key:
```sh
radosgw-admin user create --uid=admin --display-name="Tài khoản admin"
```
![](images_sse_s3/anh3.png)

 - Lưu thông tin của access_key và secret_ket
 - Nếu quên ta có thể  lấy `access_key` và `secret_key`:
  - Liệt kê user:
```sh 
  radosgw-admin user list
  ```
  - Xem chi tiết từng user và lấy `access_key`, `secret_key`
```sh
  radosgw-admin user info --uid=admin
  ```
Bước 3: Cấu hình Multi-site bằng radosgw-admin
```sh
# 1. Tạo Realm
sudo radosgw-admin realm create --rgw-realm=myorg --default

# 2. Tạo Zonegroup
sudo radosgw-admin zonegroup create --rgw-zonegroup=us-east-zg-1 --endpoints=http://192.168.1.106:7480 --master --default

# 3. Tạo Zone
sudo radosgw-admin zone create --rgw-zonegroup=us-east-zg-1 --rgw-zone=us-east-1 --master --default

# 4. Cập nhật period để áp dụng cấu hình
sudo radosgw-admin period update --commit
```
Bước 4: Cài đặt, configure aws-cli để config bucket
- Cài đặt aws-cli
```sh
sudo yum remove awscli
curl "https://awscli.amazonaws.com/awscli-exe-linux-x86_64.zip" -o "awscliv2.zip"
unzip awscliv2.zip
sudo ./aws/install
aws --version
```
![](images_sse_s3/anh4.png)
- Configure aws-cli (Điền access_key và secret_key như trên đã lưu lại)
```sh
aws configure
```
![](images_sse_s3/anh5.png)

- Cài đặt 
Bước 4: Tạo bucket với aws-cli tại endpoint cụ thể: 
```sh
aws s3 mb --endpoint http://192.168.1.106:7480 s3://khiem.mmt1.test --region us-east-1 
```
![](images_sse_s3/anh26.png)

Bước 5: Tạo policy để bucket có thể truy cập public
```sh
vi public.json
{
  "Version":"2012-10-17",
  "Statement":[{
    "Sid":"PublicRead",
    "Effect":"Allow",
    "Principal":"*",
    "Action":["s3:GetObject","s3:ListBucket"],
    "Resource":[
      "arn:aws:s3:::khiem.mmt1.test",
      "arn:aws:s3:::khiem.mmt1.test/*"
    ]
  }]
}

```
Bước 6: Áp dụng policy cho bucket
```sh
aws   --endpoint-url http://192.168.1.106:7480   s3api put-bucket-policy   --bucket khiem.mmt1.test  --policy file://public.json
```
Bước 5: Tạo, put, get file vừa tạo qua dịch vụ S3
- Put dữ liệu lên
```sh
echo "hihihaha" >> test.txt
aws --endpoint http://192.168.1.106:7480 s3 cp test.txt s3://khiem.mmt1.test/test
aws s3api head-object --bucket khiem.mmt1.test --key test --endpoint-url http://192.168.1.106:7480
 ```
![](images_sse_s3/anh27.png)
- GET dữ liệu về: 
```sh
aws s3 cp s3://khiem.mmt1.test/test download_file.txt --endpoint-url http://192.168.1.106:7480
```
![](images_sse_s3/anh28.png)