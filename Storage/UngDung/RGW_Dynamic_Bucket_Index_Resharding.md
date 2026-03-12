# RGW Dynamic Bucket Index Resharding

## Định nghĩa

- RGW Dynamic Bucket Index Resharding (Phân mảnh Index tự động) là một trong các tính năng tự động của Ceph Object Gateway giúp duy trì hiệu suất hệ thống khi có dữ liệu lớn

## Cách hoạt động

- Resharding (Phân mảnh): Là quá trình chia cắt một Bucket Index thành nhiều phần nhỏ (shards). Thay vì 1 OSD gánh một index khổng lồ thì nó sẽ được phân mảnh và chia đều cho các OSD

- Dynamic (Động): Trước bản Luminios, các quản trị viên sẽ tự config bằng tay dẫn đến khi đó các bucket sẽ bị đóng băng không thêm được object mới. Với các phiên bản sau Dynamic Resharding trở thành backgroud threads sẽ tự động làm các việc như:
  - Liên tục theo dõi số lượng của các Bucket
  
  - Khi số lượng object trên một shard vượt quá số lượng cho phép, RGW sẽ lên lịch và tự động phân mảnh bucket đó

  - RGW tạo ra một tập hợp các shard index mới ở chế độ nền

  - Swap các shard mà không gây gián đoạn cho các thao tác đọc ghi của người dùng

  - Xóa các index cũ để giải phóng dung lượng

  ## Thông số cấu hình cốt lõi

  - `rgw_dynamic_resharding` (Mặc định là true): Cho phép bật/tắt chế độ resharding

  - `rgw_max_objs_per_shard` (Mặc định là 100000): Ngưỡng kích hoạt khi object trong 1 shard vượt quá thì sẽ lên lich reshading 
  
  - `rgw_thread_pool_size`: Quá trình resharding cần sử dụng tài nguyên luồng RGW để khi chạy ngầm không bị chậm

  - `rgw_reshard_num_logs`: Số lượng shard của tiến trình resharding

