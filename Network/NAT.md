NAT
1. Khai niệm NAT
- NAT (Network Address Translation) là kỹ thuật chuyển đổi địa chỉ IP trong các gói tin mạng khi chúng đi qua một thiết bị định tuyến hoặc tường lửa.
- Mục đích chính của NAT là tiết kiệm địa chỉ IP công cộng và tăng cường bảo mật cho mạng nội bộ.
- Có ba loại NAT phổ biến:
  - SNAT (Source NAT): Thay đổi địa chỉ IP nguồn của gói tin khi nó rời khỏi mạng nội bộ.
  - DNAT (Destination NAT): Thay đổi địa chỉ IP đích của gói tin khi nó đến mạng nội bộ.
  - Masquerade: Một dạng đặc biệt của SNAT, thường được sử dụng khi địa chỉ IP công cộng thay đổi động (ví dụ: kết nối Internet qua ISP).
2. Cách hoạt động của NAT
- Khi một thiết bị trong mạng nội bộ gửi gói tin ra ngoài Internet, NAT sẽ thay đổi địa chỉ IP nguồn của gói tin thành địa chỉ IP công cộng của thiết bị định tuyến.
- Khi gói tin phản hồi từ Internet quay trở lại, NAT sẽ thay đổi địa chỉ IP đích trở lại địa chỉ IP nội bộ ban đầu của thiết bị gửi.
- NAT duy trì một bảng ánh xạ để theo dõi các kết nối và đảm bảo rằng các gói tin được chuyển tiếp đúng cách.
