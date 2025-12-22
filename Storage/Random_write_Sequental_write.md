# RANDOM WRITE VÀ SEQUENTIAL WRITE
## 1. Khái niệm
- Random write và Sequential write là hai phương thức ghi dữ liệu vào bộ nhớ lưu trữ
## 2. Phân biệt
- Random write là dữ liệu được ghi rải rác vào các khối bộ nhớ không liên tiếp nhau, không theo một trật tự nhất định nào cả
- Sequential write là dữ liệu được ghi liên tiếp vào các khối bộ nhớ(block) theo một trật tự nhất định 
## 3. So sánh tốc độ và Throughtput của Random write và Sequential write
- Sequential write thường có tốc độ và Throughtput cao hơn so với Random write vì dữ liệu được ghi liên tiếp, giúp giảm thiểu thời gian tìm kiếm và di chuyển đầu đọc/ghi trên ổ cứng
- Random write thường có tốc độ và Throughtput thấp hơn do dữ liệu được ghi rải rác, bộ điều khiển phải tính toán địa chỉ cho từng gói dữ liệu nhỏ dẫn đến việc đầu đọc/ghi phải di chuyển nhiều hơn để tìm vị trí ghi dữ liệu
## 4. Use case  
- Random write thường được sử dụng trong các hệ thống đang chạy với nhiều tập tin nhỏ như cơ sở dữ liệu, máy ảo, hệ thống tập tin,...
- Sequential write thường được sử dụng trong các hệ thống lưu trữ lớn, xử lý các tập tin lớn như video, hình ảnh, sao lưu dữ liệu,...