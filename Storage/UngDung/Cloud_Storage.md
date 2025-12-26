# Cloud Storage
  ## File Storage 

  ![](images_cloud/anh1.png)

  1. Khái niệm
   - Là loại lưu trữ sử dụng cấu trúc thư mục truyền thống như trên máy tính hoặc server để lưu trữ, dược truy cập thông qua giao thức Server Message Block (SMB) trên Window hoặc NFS (Network File System) trên Linux
   - Trên Cloud đây là dịch vụ NAS (Network Attached Storage), thay vì bạn tự lập 1 con Linux cài NFS để mount vào thì nhà cung cấp Cloud đã làm hết cho bạn, bạn chỉ cần vào và dùng
  2. Ưu điểm 
   - Dễ chia sẻ tài nguyên cho nhiều người cùng lúc
   - Dễ sử dụng vì cấu trúc cây quen thuộc với người dùng
   - Sử dụng giao thức mạng phổ biến, không cần thêm client phúc tạp
  3. Nhược điểm
   - Tốc độ chậm, khi lên tới hành triệu file thì tìm kiếm sẽ khó khăn nên lúc đấy tốc độ sẽ rất chậm
   - Khó mở rộng khi hết dung lượng 
  ## Block Storage

   ![](images_cloud/anh2.png)

  1. Khái niệm 
    - Là phương pháp lưu trữ cấp thấp. Block storage sẽ quản lý và luư trữ một cụm đơn vị gọi là các khối. Các khối này sẽ được gán 1 đia chỉ duy nhất, lưu trữ trảu đều ra máy và mỗi khối sẽ lưu một phần dữ liệu của file. Khi Client gửi thông tin request tới và muỗn truy xuất tệp, Khi requst đã được duyệt thánh block request, file sẽ tập hợp chúng lại và trả về máy

  2. Ưu  điểm
    - Hoạt động có độ trễ thấp 
    - Các block thường được sao chép trên các thiết bị nên đảm bảo rằng thiết bị dữ liệu có thể khôi phục được nếu bị hỏng
  3. Nhược điểm 
    - Có thể sẽ không mở rộng được quy mô sau khi đạt đến giới hạn của bộ nhớ
  ## Object Storage

  ![](images_cloud/anh2.png)

  - Là dạng lưu trữ hiện đại trong Cloud, lưu trữ dữ liệu dưới dạng Object trong 1 không gian phẳng (Flat namespace), nơi mà không có phân cấp thư mục 