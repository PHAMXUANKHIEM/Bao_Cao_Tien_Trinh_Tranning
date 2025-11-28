--- Trong trình VIM có 4 chế độ:
 -- Normal mode: Dùng copy ,xóa, di chuyển con trỏ, paste (mở VIM lên sẽ ở chế độ này). Các lệnh cơ bản trong mode này:
  - Di chuyển: h: sang trái
               j: xuống dưới
               k: lên trên
               l: sang phải
               w: nhảy đến cuối của từ mà con trỏ đang ở
               b: nhảy lại về ban đầu của từ
               G: nhảy tới cuối file
               gg: nhảy lên đầu file 
               $: về cuối dòng
               0: về đầu dòng
 -- Insert mode: Để chỉnh sửa nội dung văn bản ta ở chế độ này. 
  - Các option: - Đánh văn bản: i: Gõ ngay ở vị trí con trỏ
                                o: Tạo 1 dòng mới bên dưới và gõ
                                0: Tạo 1 dòng mới bên trên và gõ
                                a: Gõ sau vị trí con trỏ
                - Xóa văn bản:  x: xóa 1 kí tự 
                                dw: xóa 1 từ 
                                dd: xóa cả dòng
                                3dd: xóa 3 dòng
                                u: quay lại thao tác trước
                                ctrl+r: thực hiện lại thao tác trước khi undo
                - Copy, paste:  yy: copy cả dòng hiện tại 
                                yw: copy từ hiện tại
                                p: paste dưới con trỏ
                                P: paste trên con trỏ
                - Bôi đen:      V + [h,j,k,l]: bôi đen lên xuống
                - Tìm văn bản: /ten_can_tim 