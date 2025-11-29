Glance 
1. Khai niệm Glance
- Glance là thành phần quản lý images máy ảo trong OpenStack, chịu trách nhiệm lưu trữ, truy xuất và quản lý các hình ảnh máy ảo (VM images).   
- Mục đích chính của Glance bao gồm:
  - Cung cấp dịch vụ lưu trữ và quản lý hình ảnh máy ảo cho các thành phần khác trong OpenStack.
  - Hỗ trợ nhiều định dạng hình ảnh khác nhau như QCOW2, RAW, VMDK, v.v.
  - Tích hợp với các dịch vụ khác trong OpenStack như Nova (compute) để cung cấp hình ảnh máy ảo khi cần thiết.
- Glance thường được sử dụng trong các môi trường đám mây công cộng và riêng tư để cung cấp hình ảnh máy ảo cho người dùng và các dịch vụ khác.
- Glance bao gồm các thành phần chính như:
  - Glance API: Cung cấp giao diện lập trình ứng dụng để tương tác với dịch vụ Glance.
  - Glance Registry: Quản lý metadata của các hình ảnh máy ảo.
  - Glance Store: Lưu trữ trữ các hình ảnh máy ảo trên các backend khác nhau như file system, object storage, v.v.
2. Cách hoạt động của Glance
- Khi người dùng hoặc dịch vụ khác trong OpenStack gửi yêu cầu tải lên hoặc truy xuất hình ảnh máy ảo thông qua giao diện API của Glance, Glance sẽ thực hiện các bước sau:
  1. Xác thực và ủy quyền yêu cầu từ người dùng hoặc dịch vụ.
  2. Đối với yêu cầu tải lên, Glance sẽ lưu trữ hình ảnh máy ảo vào Glance Store và lưu metadata liên quan trong Glance Registry. 
  3. Đối với yêu cầu truy xuất, Glance sẽ tìm kiếm hình ảnh máy ảo trong Glance Store và trả về hình ảnh cùng với metadata liên quan.
- Glance cũng tích hợp với các dịch vụ khác trong OpenStack để cung cấp hình ảnh máy ảo khi cần thiết, ví dụ như khi Nova yêu cầu một hình ảnh để tạo máy ảo.
3. Ứng dụng của Glance trong OpenStack
- Glance được sử dụng rộng rãi trong các môi trường đám mây công cộng và riêng tư để quản lý hình ảnh máy ảo.
- Các ứng dụng chính của Glance trong OpenStack bao gồm:
  - Lưu trữ và quản lý hình ảnh máy ảo cho các máy ảo và dịch vụ đám mây.
  - Cung cấp hình ảnh máy ảo cho các thành phần khác trong OpenStack như Nova khi cần thiết.
  - Hỗ trợ nhiều định dạng hình ảnh máy ảo để đáp ứng các yêu cầu đa dạng của người dùng.
- Glance giúp đảm bảo tính linh hoạt, mở rộng và quản lý hiệu quả hình ảnh máy ảo trong môi trường đám mây OpenStack.
4. Cấu hình Glance
- Cài đặt Glance trên máy chủ OpenStack bằng cách sử dụng các công cụ quản lý gói như apt hoặc yum.
- Cấu hình tệp cấu hình Glance (thường là glance-api.conf và glance-registry.conf) để thiết lập các thông số như cơ sở dữ liệu, backend lưu trữ, và các điểm cuối dịch vụ.
- Thiết lập cơ sở dữ liệu cho Glance để lưu trữ metadata của hình ảnh máy ảo.
- Cấu hình backend lưu trữ trong Glance Store để xác định nơi lưu trữ các hình ảnh máy ảo.
- Tạo các dịch vụ và điểm cuối trong Keystone để các thành phần khác trong OpenStack có thể truy cập Glance.
- Kiểm tra và xác nhận hoạt động của Glance bằng cách sử dụng các công cụ dòng lệnh OpenStack CLI hoặc giao diện người dùng Horizon.
- Duy trì và cập nhật Glance định kỳ để đảm bảo an ninh và hiệu suất hoạt động tốt trong môi trường OpenStack.  
5. Bảo mật Glance
- Sử dụng các phương thức xác thực mạnh mẽ thông qua Keystone để đảm bảo an ninh.
- Mã hóa thông tin nhạy cảm như hình ảnh máy ảo trong quá trình truyền tải và lưu trữ.
- Giới hạn quyền truy cập vào Glance chỉ cho các dịch vụ và người dùng cần thiết.
- Theo dõi và ghi lại các hoạt động liên quan đến việc tải lên và truy xuất hình ảnh máy ảo để phát hiện các hành vi đáng ngờ.
- Cập nhật Glance và các thành phần liên quan định kỳ để vá các lỗ hổng bảo mật.
- Sử dụng các công cụ giám sát và cảnh báo để theo dõi tình trạng bảo mật của Glance trong môi trường OpenStack.
6. Tích hợp Glance với các dịch vụ khác trong OpenStack
- Cấu hình các dịch vụ khác trong OpenStack như Nova để sử dụng Glance làm dịch vụ quản lý hình ảnh máy ảo.
- Thiết lập các điểm cuối dịch vụ trong Keystone để các dịch vụ khác có thể kết nối và tương tác với Glance.
- Sử dụng hình ảnh máy ảo do Glance quản lý để tạo máy ảo trong Nova.
- Quản lý quyền truy cập hình ảnh máy ảo thông qua Keystone để đảm bảo an ninh và kiểm soát truy cập.
- Kiểm tra và xác nhận tích hợp giữa Glance và các dịch vụ khác để đảm bảo hoạt động trơn tru trong môi trường OpenStack.
- Duy trì và cập nhật tích hợp định kỳ để đảm bảo tính tương thích và an ninh giữa Glance và các dịch vụ khác trong OpenStack.