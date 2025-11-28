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
# Vim — Tổng quan

Vim là một trình soạn thảo văn bản mạnh mẽ, hoạt động trên nhiều chế độ. Dưới đây là các chế độ và lệnh cơ bản để làm việc hiệu quả.

## Các chế độ chính

- **Normal mode** (mặc định khi mở Vim): dùng để điều hướng, xóa, copy/paste, chạy lệnh.
- **Insert mode**: chèn/soạn văn bản.
- **Visual mode**: chọn vùng văn bản (tương tự bôi đen).
- **Command-line mode** (dấu `:`): nhập lệnh lưu/thoát, tìm kiếm, thay thế.

## Lệnh chuyển chế độ

```text
i    # vào Insert mode (chèn trước con trỏ)
a    # vào Insert mode (chèn sau con trỏ)
o    # mở dòng mới bên dưới và vào Insert
v    # vào Visual mode (chọn ký tự)
V    # Visual line (chọn cả dòng)
<Esc># trở về Normal mode
:
```

## Di chuyển (Normal mode)

- `h` trái, `j` xuống, `k` lên, `l` phải
- `w` nhảy tới đầu từ kế tiếp, `b` về đầu từ trước
- `0` về đầu dòng, `$` về cuối dòng
- `gg` tới đầu file, `G` tới cuối file

## Chỉnh sửa và xóa

- `i`/`a`/`o` để vào Insert mode và gõ văn bản
- `x` xóa ký tự dưới con trỏ
- `dw` xóa một từ
- `dd` xóa cả dòng; `3dd` xóa 3 dòng

## Hoàn tác và làm lại

- `u` hoàn tác (undo)
- `<Ctrl>-r` làm lại (redo)

## Sao chép và dán (yank & paste)

- `yy` (yank) sao chép cả dòng
- `yw` sao chép một từ
- `p` dán dưới con trỏ, `P` dán trên con trỏ

## Visual mode (chọn vùng)

- `v` rồi di chuyển con trỏ để chọn ký tự
- `V` chọn nguyên dòng
- Nhấn `y` để sao chép, `d` để xóa, `>`/`<` để thụt đầu dòng

## Tìm kiếm và thay thế

- Tìm: `/ten_can_tim` rồi `n` để tới kết quả kế tiếp
- Thay thế trên toàn file: `:%s/old/new/g`
- Thay thế với hỏi xác nhận: `:%s/old/new/gc`

## Lưu và thoát

- `:w` lưu file
- `:q` thoát
- `:wq` lưu và thoát
- `:q!` thoát không lưu

## Một số mẹo nhanh

- Thêm số dòng: `:set number`
- Chuyển sang dòng số N: `:N` (ví dụ `:42`)
- Xóa khoảng trắng cuối dòng: `:%s/\s\+$//e`

---

Tài liệu trên trình bày các lệnh phổ biến để bắt đầu với Vim. Nếu bạn muốn tôi format lại theo một mẫu cụ thể (bảng, checklist, hay ví dụ chi tiết hơn), cho biết kiểu trình bày mong muốn.