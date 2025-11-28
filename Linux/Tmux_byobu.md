 3.1 Tmux
  --- Là bộ tách terminal, cho phép các terminal chạy 1 cách độc lập mà vẫn giữ nguyên các chương trình chạy trên terminal đó
   -- Cách tạo: 
    - Tạo mới tmux: tmux: tạo mới 1 session
                    tmux a: attach vào session 
                    tmux new -s ten_session: tạo 1 session mới nhưng có tên
                    tmux a -t ten_sesssion: attach vào session có tên
                    tmux kill-session -t ten_session: xóa session đó
    - Lệnh trong tmux: Lệnh làm việc với cửa sổ: ctrl+b c: tạo thêm 1 cửa sổ
                                                 ctrl+b ,: đổi tên 1 cửa sở 
                                                 ctrl+b n,p: vào cửa sổ trước hoặc sau
                                                 ctrl+b f: Tìm tên cửa sổ
                                                 ctrl+b %: Đóng cửa sổ
                       Lệnh với panel: ctrl+b %: chia đôi màn hình theo chiều dọc
                                       ctrl+b ": chia đôi màn hình theo chiều ngang
                                       ctrl+b o: di chuyển giữa các panel
                                       ctrl+b x: xóa panel
 3.2 Byobu
  --- Giong voi Tmux nhung co mau va cac phim tat de su dung hon 
  --- Cac lenh tron byobu: 
   -- Tao moi: -F2: tao moi cua so 
               -Shift-F2: chia moi cua so theo chieu ngang
               -Ctrl-F2: chia moi cua so theo chieu doc
               -Ctrl-Shift-F2: Tao moi session
   -- Di chuyen: -<F3><F4> hoac Alt-left/right: di chuyen qua lai giua cac window
                 -Alt + len/xuong: di chuyen qua lai giua cac sessions
                 -Shift + len/xuong/trai/phai hoac Shift + <F3><F4>: di chuyen giua cac cua so chia
                 - Ctrl + <F3><F4>: di chuyen man hinh chia tu ben nay sang ben kia
                 - Ctrl + Shift + <F3><F4>: di chuyen man hinh tu cua so nay sang cua so khac
                 - Shift + Alt + Trai/Phai/Len/Xuong: thay doi kich thuoc man hinh chia
   -- Reload: <F5> reload lai trang, refresh status
   -- Thoat: -<F6>: tach session va logout
             -Shift + <F6> : tach session nhung khong logout
             -Ctrl + <F6>: kill spilt
   -- Chay dong thoi: -Ctrl <F9>: chay cac lenh tren tat ca cac window
                      -Shift <F9>: chay cac lenhh tren tat ca cac man hinh chia
   -- Phong to man hinh: - F11: phong to man hinh chia 