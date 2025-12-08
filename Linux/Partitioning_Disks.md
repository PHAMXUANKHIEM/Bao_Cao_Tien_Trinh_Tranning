# Partition Disk
## 1. Khái niệm 
- Partition (phân vùng) là cách chia ổ đĩa vật lý thành các phần nhỏ hơn.
- Có 2 cách để partition:
 _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
|                       |               Ưu điểm               |              Nhược điểm               |
|_ _ _ _ _ _ _ _ _ _ _ _|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _| _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ |
|                       | - Hoạt động tốt trên tất cả các nền | - Dữ liệu MBR được lưu trữ trên 1 vùng|
|                       | tảng Window hiện nay                |nhất định vì thế dễ bị lỗi và không có |
|         MBR           |                                     |khả năng khôi phục                     |
|                       |                                     | - Hỗ trợ tối đa 4 phân vùng chính     | 
|                       |                                     | - Muốn tạo nhiều phân vùng thì phải   |
|                       |                                     |tạo kiểu Logical                       |
|_ _ _ _ _ _ _ _ _ _ _ _|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
|                       |- Hoạt động tốt trên hệ điều hành Mac|                                       |
|                       |Window, Linux                        |                                       |
|                       |- Dễ dàng khôi phục dữ liệu vì GPT   |                                       |
|          GPT          |chạy trên nhiều ổ cứng               |                                       |
|                       |                                     |                                       |
|                       |                                     |                                       |
|_ _ _ _ _ _ _ _ _ _ _ _|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _| _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ |