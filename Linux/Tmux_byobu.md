## 3.1 Tmux

- **Giới thiệu**  
  Tmux là bộ tách terminal, cho phép các terminal chạy một cách độc lập mà vẫn giữ nguyên các chương trình đang chạy trên terminal đó.

- **Cách tạo:**  
  - Tạo mới tmux:  
    - `tmux`: tạo mới một session  
    - `tmux a`: attach vào session  
    - `tmux new -s <ten_session>`: tạo một session mới với tên  
    - `tmux a -t <ten_session>`: attach vào session có tên  
    - `tmux kill-session -t <ten_session>`: xóa session đó  

- **Lệnh trong tmux:**  
  - Làm việc với cửa sổ:  
    - `Ctrl+b c`: tạo thêm một cửa sổ  
    - `Ctrl+b ,`: đổi tên một cửa sổ  
    - `Ctrl+b n`, `Ctrl+b p`: vào cửa sổ trước hoặc sau  
    - `Ctrl+b f`: tìm tên cửa sổ  
    - `Ctrl+b &`: đóng cửa sổ  
  - Làm việc với panel:  
    - `Ctrl+b %`: chia đôi màn hình theo chiều dọc  
    - `Ctrl+b "`: chia đôi màn hình theo chiều ngang  
    - `Ctrl+b o`: di chuyển giữa các panel  
    - `Ctrl+b x`: xóa panel  

---

## 3.2 Byobu

- **Giới thiệu**  
  Giống với Tmux nhưng có màu và các phím tắt dễ sử dụng hơn.

- **Các lệnh trong Byobu:**  
  - **Tạo mới:**  
    - `F2`: tạo mới cửa sổ  
    - `Shift+F2`: chia cửa sổ theo chiều ngang  
    - `Ctrl+F2`: chia cửa sổ theo chiều dọc  
    - `Ctrl+Shift+F2`: tạo mới session  
  - **Di chuyển:**  
    - `<F3>/<F4>` hoặc `Alt+Left/Right`: di chuyển qua lại giữa các window  
    - `Alt+Up/Down`: di chuyển qua lại giữa các sessions  
    - `Shift+Up/Down/Left/Right` hoặc `Shift+<F3>/<F4>`: di chuyển giữa các cửa sổ chia  
    - `Ctrl+<F3>/<F4>`: di chuyển màn hình chia từ bên này sang bên kia  
    - `Ctrl+Shift+<F3>/<F4>`: di chuyển màn hình từ cửa sổ này sang cửa sổ khác  
    - `Shift+Alt+Left/Right/Up/Down`: thay đổi kích thước màn hình chia  
  - **Reload:**  
    - `F5`: reload lại trang, refresh status  
  - **Thoát:**  
    - `F6`: tách session và logout  
    - `Shift+F6`: tách session nhưng không logout  
    - `Ctrl+F6`: kill split  
  - **Chạy đồng thời:**  
    - `Ctrl+F9`: chạy các lệnh trên tất cả các window  
    - `Shift+F9`: chạy các lệnh trên tất cả các màn hình chia  
  - **Phóng to màn hình:**  
    - `F11`: phóng to màn hình chia  