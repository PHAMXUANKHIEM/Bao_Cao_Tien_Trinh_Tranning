# RBD
## Khái niệm 
- RBD (RADOS Block Devices): lưu trữ khối làm backend cho Cinder và Nova trong Openstack. 

![](images_RADOS/anh10.png)

## Cách hoạt động 
- RBD sẽ xé nhỏ dữ liệu của bạn thành các block và phân tán vào các OSD
- Khi một máy linux kết nối tới RBD, chúng sẽ nhìn thấy nó như 1 ổ cứng vật lý cắm trực tiếp `/dev/rdb0` có thể mount format chúng và cài đặt hệ điều hành lên nó
## Đặc điểm kĩ thuật
- Striping: Dữ liệu được cắt xé và phân tán song song vào các OSD
- Thin Provisioning: Kĩ thuật này chỉ cho ta thấy lời hứa. Ví dụ tổng disk của các OSD là 300GB nhưng nhờ kĩ thuật này ta có thể đẩy con số lên 500GB mặc dù 200GB còn lại là ảo
- Snapshot và Clone: Tạo bản snapshot và nhân bản cực nhanh



