Bước 1: Tạo lại root token mới 
```sh
vault operator generate-root -init
```
- Sau câu lệnh trên sẽ trả về 1 mã otp. Lưu lại

![](images_sse_s3/anh40.png)

Bước 2: Lấy mã encode của root token
```sh
vault operator generate-root
```
- Nhập 3 lần mã Unseal đã lưu và nó sẽ trả về 1 mã encode

![](images_sse_s3/anh41.png)

Bước 3: Lấy lại root token
```sh
vault operator generate-root -decode=<encoded_token> -otp=<otp>
```

![](images_sse_s3/anh42.png)
