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
  - Khi đó mỗi dữ liệu sẽ được chia thành các đối tượng riêng lẻ và được gắn mã định danh duy nhất. Mỗi đối tượng (object) sẽ gồm 3 thành phần chính:
   - Dữ liệu
   - Metadata
   - ID định danh
   ## So sánh
   | Tiêu chí | Object Storage | File Storage | Block Storage |
| :--- | :--- | :--- | :--- |
| **Cách tổ chức dữ liệu** | Dữ liệu được lưu trữ dưới dạng đối tượng (objects), cấu trúc phẳng (flat), không có thư mục. | Dữ liệu được tổ chức phân cấp trong các thư mục và tệp tin (hierarchical). | Dữ liệu được chia thành các khối (blocks) nhỏ, thô, quản lý bởi hệ điều hành máy chủ. |
| **Khả năng mở rộng** | Mở rộng linh hoạt, gần như không giới hạn (Scale-out). | Khó mở rộng khi dữ liệu tăng nhanh, thường giới hạn bởi thiết bị phần cứng. | Mở rộng dễ dàng nhưng chi phí cao, thường giới hạn bởi controller/mảng đĩa. |
| **Cách truy cập** | Truy cập thông qua API (RESTful) bằng mã định danh (ID) duy nhất. | Truy cập qua giao thức chia sẻ file (NFS, SMB) theo đường dẫn cụ thể. | Truy cập trực tiếp ở cấp độ khối thông qua hệ điều hành (như một ổ đĩa vật lý). |
| **Hiệu suất** | Tốc độ truy cập không cao bằng Block, độ trễ cao hơn nhưng băng thông lớn. | Tốc độ truy cập nhanh, phù hợp với hệ thống chia sẻ nội bộ, user truy cập đồng thời. | Hiệu suất rất cao (IOPS cao, độ trễ thấp), phù hợp giao tiếp trực tiếp với CPU. |
| **Chi phí lưu trữ** | Thấp nhất. Tiết kiệm chi phí cho dữ liệu lớn, khổng lồ. | Chi phí trung bình đến cao (do phần cứng NAS chuyên dụng). | Chi phí cao nhất (High performance SAN/SSD). |
| **Ứng dụng chính** | Lưu trữ backup, archive, static web, dữ liệu phi cấu trúc (video, ảnh, IoT). | Lưu trữ tệp chia sẻ văn phòng, thư mục home directory, repository code. | Cơ sở dữ liệu (Database), ổ đĩa boot cho máy ảo (VM), ứng dụng mission-critical. |
