# Linstor

## DRBD

- DRBD (Distributed Replicated Block Device) hoạt động dưới dạng một module tích hợp trực tiếp trong nhân hệ diều hành Linux. Chức năng chính của DRBD là thực hiện sao chép dữ liệu ở cấp độ block-level giữa hai hay nhiều máy chủ độc lập thông qua TCP/IP theo thời gian thực.

- Nói đơn giản là nó sẽ sao chép dữ liệu trên thiết bị chính cho các thiết bị phụ mà đảm bảo rằng dữ liệu vẫn giống hệt nhau như cách RAID 1 hoạt động nhưng thông qua mạng TCP/IP

- Phần mềm DRBD sẽ đảm nhận việc đồng bộ này. Khi được cài đặt trên hai hay nhiều máy chủ trong một nhóm cluster, drbd sẽ thực hiện liên tục đồng bộ các partition ổ cứng được chỉ định thông qua mạng. Nói cách khác khi một lệnh ghi ổ cứng trên máy chủ chính chỉ được tính là hoàn thành khi lệnh đó cũng được thực hiện xong trên các máy khác ở trong cluster

## Linstor

- Là giải pháp quản trị và điều phối lưu trữ

- Chức năng cốt lõi là tự động hóa quá trình cấp phát, quản lý, cấu hình, giám sát các tài nguyên lưu trữ khối trên các cụm máy chủ lưu trữ phân tán

- Linstor hoạt động hoàn toàn về mặt điều khiển, nó không trực tiếp chứa dữ liệu, không xử lý hay can thiệp vào luồng I/O của hệ thống. Thay vào đó nó giống như trung tâm tiếp nhận yêu cầu và chỉ thị cho các nút lưu trữ bên dưới thực thi

- Thay vì tạo ra một hệ thống tập tin mới hay định dạng khối mới, Linstor tự động hóa các quá công nghệ lưu trữ gốc bản địa đã được kiểm chứng của nhân Linux. Quá trình này bao gồm việc khởi tạo không gian lưu trữ thông qua LVM, LVM-Thin hoặc ZFS kết hợp với DRBD để thiết lập cơ chế đồng bộ hóa dữ liệu qua mạng nhằm đảm bảo tính HA cho hệ thống

- Hệ thống vân hành Linstor gồm 2 phần lõi:

  - Linstor controller: Bộ não điều khiển trung tâm, chịu trách nghiệm sao lưu metadata của cụm, tính toán thuật toán cấp phát và phân phối lệnh

  - Linstor Satellite: Các agent được cài đặt trên từng máy chủ vật lý làm nhiệm vụ lắng nghe và trực tiếp thực thi các lệnh từ Controller xuống cấp độ hệ điều hành


