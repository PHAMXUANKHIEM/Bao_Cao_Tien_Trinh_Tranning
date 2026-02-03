# Triển khai SSE-KMS
### Cài đặt Hashicorp Vault
Bước 1: Tải gói và cài đặt 
```sh
yum install yum-utils
yum-config-manager --add-repo https://rpm.releases.hashicorp.com/RHEL/hashicorp.repo
yum -y install vault
```
Bước 2: Cấu hình Vault trong `/etc/vault.d/vault.hcl`:
```sh
storage "file" {
  path = "/opt/vault/data"
}

listener "tcp" {
  address     = "192.168.1.138:8200"
  tls_disable = 1
}
api_addr = "http://192.168.1.138:8200"
ui = true
disable_mlock = true
``` 
Bước 3: Kiểm tra
```sh
export VAULT_ADDR="http://192.168.1.138:8200"
vault status
```
![](images_sse_s3/anh9.png)

Bước 4: Lấy mã Unseal và root token 
```sh
vault operator init
```
![](images_sse_s3/anh10.png)

***LƯU Ý: PHẢI LƯU LẠI CÁC KEY NÀY ĐỂ BƯỚC SAU UNSEAL***

Bước 6:  Khi chưa nhập mã Unseal, Vault luôn trong trạng thái sealed. Ở trạng thái này Vault không thể giải mã dữ liệu nào ở bên trong và mọi secret đều bị từ chối. Nhập Unseal Vaule (3 lần) và mỗi lần nhập 1 loại Unseal khác nhau để giá trị unseal process trả về 3/3.
```sh
vault operator unseal 
```
![](images_sse_s3/anh11.png)

Bước 7: Đăng nhập và bật chế độ transit secret
```sh
vault login 
vault secrets enable transit
```
![](images_sse_s3/anh13.png)

### Cấu hình SSE-KMS
#### Cephadm (RGW container)
- Trước hết ta cần tạo trên Vault 1 transit để lưu trữ thông tin mã hóa 
```sh
vault write -f transit/keys/ceph-bucket-key exportable=true allow_plaintext_backup=true ##Cấu hình exportable=true quan trọng để khi Ceph cần giải mã ở lớp Gateway, KMS gửi khóa này về bộ nhớ RAM để xử lý
```
- Khi đã tạo xong key kết nối tới transit, ta cần tạo file policy để có phép các bucket có quyền gì khi sử dụng key đó
```sh
#  Cho phép Ceph truy cập vào metadata và lấy thông tin về khóa có tên là ceph-bucket-key
path "transit/export/encryption-key/ceph-bucket-key" {
  capabilities = ["read"]
}
# Đây là quyền quan trọng nhất để lấy giá trị thực của khóa (phiên bản số 1).
path "transit/export/encryption-key/ceph-bucket-key/1" {
  capabilities = ["read", "update"]
}
# Cho phép encrypt
path "transit/encrypt/ceph-bucket-key" {
  capabilities = ["update"]
}
# Cho phép decrypt
path "transit/decrypt/ceph-bucket-key" {
  capabilities = ["update"]
}
# Cho phép đọc metadata của key
path "transit/keys/ceph-bucket-key" {
  capabilities = ["read"]
}
```
- Áp dụng policy đó cho vault 
```sh
vault policy write rgw-policy rgw-policy.hcl
```
- Để SSE-KMS hoạt động, ta cần cho cấu hình để Ceph có thể kết nối tới Vault và yêu cầu sử dụng SSE-KMS
- Cấu hình Ceph kết nối tới Vault (Cấu hình này cũng sẽ tự động lưu vào trong các container nên không cần phải vào các container chạy dịch vụ rgw cấu hình lại)
```sh
# Cấu hình nơi lưu trữ encryption key mắc địch là ở đâu
ceph config set client.rgw.sse.host-192-168-1-138.dovwzs rgw_crypt_default_encryption_key ceph-bucket-key
# Cấu hình backend cho sse-kms là vault
ceph config set client.rgw.sse.host-192-168-1-138.dovwzs  rgw_crypt_s3_kms_backend vault
# Cấu hình địa chỉ truy cập Vault cho sse-kms
ceph config set client.rgw.sse.host-192-168-1-138.dovwzs  rgw_crypt_vault_addr http://192.168.1.142:8200
# Cấu hình auth để truy cập vault là token 
ceph config set client.rgw.sse.host-192-168-1-138.dovwzs  rgw_crypt_vault_auth token
# Cấu hình nơi để export thông tin dữ liệu để mã hóa
ceph config set client.rgw.sse.host-192-168-1-138.dovwzs  rgw_crypt_vault_prefix /v1/transit 
# Cấu hình nói lưu trữ là transit
ceph config set client.rgw.sse.host-192-168-1-138.dovwzs  rgw_crypt_vault_secret_engine transit
# Cấu hình đường dẫn tới file token 
ceph config set client.rgw.sse.host-192-168-1-138.dovwzs  rgw_crypt_vault_token_file /etc/ceph/vault.token 
# Cấu hình tắt truy cập bằng cert 
ceph config set client.rgw.sse.host-192-168-1-138.dovwzs rgw_crypt_require_ssl false
```
- Khi đã cấu hình cho Ceph kết nối tới Vault, restart lại dịch vụ rgw 
```sh
ceph orch restart rgw.sse
```
- Lấy ID của container và dùng podman để vào bên từng container chạy dịch vụ rgw để cấu hình đường dẫn tới vault.token
```sh
podman exec -it <ID container> /bin/bash 
vi /etc/ceph/vault.token
#(QUAN TRỌNG) Phải cấu hình đúng quyền 600 và người dùng ceph cho file token để đảm bảo tính bảo mật nếu không sẽ báo lỗi permission
chmod 600 /etc/ceph/vault.token
chown ceph:ceph /etc/ceph/vault.token
```
***LƯU Ý: NẾU RESTART LẠI CONTAINER THÌ MẶC ĐỊNH CẤU HÌNH ĐƯỜNG DẪN TỚI VAULT.TOKEN SẼ MẤT, PHẢI VÀO CẤU HÌNH LẠI***

- Để dùng dịch vụ SSE-KMS khi upload file cần phải có thêm trường gọi mã hóa `--sse aws:kms` và trường `--sse-kms-key-id ceph-bucket-key`, nếu không mặc định nó vẫn sẽ upload file thường không mã hóa lên s3
  - Upload mac dinh
```sh
 aws --endpoint-url http://192.168.1.138:8000 s3 cp test_folder s3://khiem.mmt.test/test1 --recursive # --recursive cho phép thực hiện dối với tất cả các đối tượng file trong 1 folder thay vì 1 file duy nhất
```
  - Upload khi thêm trường `--sse aws:kms` và trường `--sse-kms-key-id`
```sh
aws --endpoint-url http://192.168.1.138:8000 s3 cp test.txt s3://khiem.mmt.test/test2   --sse aws:kms --sse-kms-key-id ceph-bucket-key
```
- Kiểm tra file upload lên xem có mã hóa không dùng trường --head-object để check
```sh
aws s3api head-object --bucket khiem.mmt1.test --key test2
```
![](images_sse_s3/anh24.png)

- Do ta đã có đủ quyền access-key và secret-key nên khi đọc file đã upload server sẽ tự động giải mã và trả về cho đúng nội dung cho ta. Dùng `-` ở cuối câu lệnh `cp` hoặc `get-object` để đọc file
```sh
aws s3 cp s3://khiem.mmt1.test/test --endpoint-url http://192.168.1.138:8000 -
```
![](images_sse_s3/anh25.png)

- Ta vẫn có thể đọc file đã upload trước khi cấu hình SSE-KMS

![](images_sse_s3/anh20.png)
