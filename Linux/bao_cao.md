I. Cài đặt linux 
1.Cai dat linux tren moi truong ao hoa VMware Workstation
-- Tai ban ubuntu 24.04.3 server, ubuntu 24.04.3 desktop
-- Vao phan mem VMware Workstation chon File - New Virtual Machine - chon file iso ubuntu - chon 30G disk, 2GB ram
-- Chon Next lien tuc de cai dat 
2. Cai dat song song window bang dual boot
-- Phan vung bo nho
-- Cam USB, reset lai may va bat BIOS len
-- Chon Linux va cai dat
II. Linux
1. Nắm được các kiến thức cơ bản trong Linux
-- Các loại shell trong linux: 
 - sh: bản tiêu chuẩn chạy script trên hệ thống Unix
 - bash: nâng cao của sh có nhiều tính năng hơn và chạy chủ yếu trên Linux
 - csh: tương tự như sh và có nhiều tính năng hơn 
 - ksh : một trong những shell phổ biến nhất trên các hệ thống UNIX hỗ trợ cho biến mảng (array variables) cú pháp lặp for cải tiến 
-- Cách thay đổi thư mục làm việc dùng lệnh cd, cách xem thư mục đang làm việc dùng lệnh pwd
-- Xem lịch sử các lệnh đã gõ dùng lệnh history, cách để thực hiện 1 lệnh đã làm trong quá khứ dùng nút lên xuống để tìm kiếm
-- Biến môi trường là các giá trị hệ điều hành lưu trữ để các chương trình, shell và ứng dụng sử dụng. Để gán giá trị biến dùng lệnh export TEN_BIEN="gia_tri_gan", xem giá trị của 1 biến dùng lệnh echo $TEN_BIEN, xem toàn bộ biến của môi trường dùng lệnh env
-- Để tìm hiểu cách sử dụng chi tiết về 1 lệnh ta dùng cú pháp man [Ten_Lenh] vd: man ls
-- Khi chạy 1 chương trình hệ điều hành sẽ cho ra 3 dòng dữ liệu Standard input, Standard output, Standard error
 - Standard input (STDIN): là luồng dữ liệu đầu vào của chương trình lấy mặc định từ bàn phím. VD: lệnh cat < file.txt sẽ chuyển hướng lệnh cat tới thư mục file.txt
 - Standard output (STDOUT): là luồng dữ liệu đầu ra chuẩn, chương trình sẽ ghi kết quả vào đây và hiển thị lên terminal
 - Standard error (STDERR): là thông báo lỗi khi chương trình gửi lỗi và cũng mặc định hiển thị trên terminal
 - Piping: dùng dấu | là cách lấy stdout của chương trình A và dùng nó làm STDIN của chương trình B. VD (ip a | grep ens32) là nó sẽ chỉ hiển thị ra ens32 
--- Một số lệnh quan trọng:
 -- cat: Dùng để xem, ghép, nhân bản nội dung file. Các ví dụ câu lệnh cat và các option quan trọng gồm:
  - Xem file: cat file.txt
  - Ghép file: cat file.txt file1.txt >> output.txt
  - Ghi thêm vào file: cat file1.txt >> file2.txt
  - Tạo nhanh file: cat > newfile.txt
  - Các option: -n: đánh số dòng (kể cả dòng trống)
                -nl: chỉ đánh số các dòng có chữ
                -A: hiển thị các kí tự đặc biệt
                -b: đánh số dòng không rỗng
                -s: Xóa dòng trống lặp lại
 -- join: Kết hợp 2 file theo cột khóa giống nhau, chúng phải có chung khóa và phải được xắp xếp trước. Nếu chưa sắp xếp thì phải dùng lệnh sort. Các ví dụ câu lệnh join và các option quan trọng gồm:
  - Default join: kiểu này join sẽ mặc định lấy cột đầu tiên làm khóa. Vd: join file.txt file1.txt (cần phải chắc chắn các dòng có ID giống nhau ở đầu dòng)
  - Các option: -a [số_thứ_tự_file_muốn_in]: in hết dự liệu của 1 trong 2 file hoặc cả 2, 
                -v [số_thứ_tự_file_muốn_in]: in ra tất cả dữ liệu không khớp của 1 trong 2 file, 
                -t [char]: nếu file là CSV ngăn cách bằng dấu phẩy, 
                -o [Tên file].[Tên cột]: chỉ định tên in ra cột nào của file nào, 
                -[Số thứ tự file] [Tên cột]: để ghép in ra cột này file này sẽ được ghép với cột này file kia
                -e: điền giá trị vào ô trống   
 -- paste: Kết hợp 2 file theo hàng ngang và không dựa trên khóa. Các ví dụ câu lệnh paste và các option quan trọng gồm:
  - Ghép file: paste [option] file1.txt file2.txt
  - Các option: -d "dấu_phân_cách": thay đổi dấu phân cách 
                -s: chuyển đổi cột thành hàng ngang
 -- tac: Giống với cat dùng để đọc nội dung của file nhưng khác cat là nó sẽ đọc từ dưới lên trên thuận tiện cho việc xem log. Nó tương đương lênh tail. Câu lệnh hay dùng tac /var/log/syslog | head -n 10.
 -- sort: Sắp xếp các văn bản. Các option quan trọng gồm:
  - Các option: sort: mặc định xếp theo text
                -n: sắp xếp theo số từ bé đến lớn
                -r: sắp xếp theo số từ lớn đến bé
                -k: chọn cột để sort
                -t: chọn dấu phân cách
 --uniq: Lọc trùng lặp. Chú ý khi dùng lệnh uniq chỉ lọc ra các dòng trùng lặp khi chúng ở cạnh nhau nên phải dùng lệnh sort trước khi dùng lệnh uniq. Các option quan trọng gồm:
  - Các option: Không option: gộp các dòng trùng lại thành 1
                -c: đếm số lần xuất hiện của các dòng
                -d: chỉ in ra các dòng bị trùng 
                -u: chỉ in ra các dòng không trùng ai
 -- split: Chia nhỏ file to thành các file nhỏ hơn. Các option thường dùng:
  - Các option: -l: chia theo số dòng
                -b: chia theo dung lượng
                -d: đặt tên file thành 01, 02 sau khi chia thay vì mặc định sẽ là aa,ab,ac,...
 -- head: Đọc file ở đâu, mặc định là 10 dòng, option -n dùng để điều chỉnh số dòng cần đọc
 -- tail: Đọc file ở cuối lên, mặc định là 10 dòng , option -n dùng để điều chỉnh số dòng cần đọc và -f để xem trực tiếp các log gửi về
 -- less: Giống như cat nhưng nó sẽ không hiển thị hết tất cả các nội dung trong file mà chỉ hiển thị từng trang một trong file đó
 -- wc: Dùng để đếm, dùng các option -w: để đếm từ, -l: đếm dòng, -c: đếm chữ
 -- cut: Để cắt cột, dùng các option -d: thay đổi dấu ngăn, -f: để lấy cột thứ
 -- grep: Để lọc dòng, dùng các option:
  - Các option: -i: Không phân biệt chữ hoa chữ thường
                -v: Loại bỏ các dòng không có từ tìm kiếm
                -r: Tìm trong thư mục, kể cả thư mục con
 -- sed: Tìm đoạn text và thay thế nó bằng đoạn khác. Các lệnh cơ bản và 1 số option:
  - Lệnh sed 's/cũ/mới/g': Nó không thay thế trong file 
  - Các option: -i: sẽ sửa đổi trực tiếp tất cả các cũ bằng mới
 -- awk: Xử lý dữ liệu bảng
2.VIM
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
3.Tmux va byobu
 3.1 tmux
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
4.Lệnh xem tiến trình
--- Các loại tiến trình:
 -- Foreground Processes: Là quy trình mà người dùng tương tác trực tiếp, có độ ưu tiên cao nhất, và được hiển thị thông báo để người dùng biết nó đang chạy
 -- Background Processes: Là quy trình chạy ngầm mà người dùng không chú ý, có độ ưu tiên thấp hơn và không được hiển thị thông báo
--- Các lệnh xem tiến trình: 
 -- ps: Hiển thị các tiến trình tại 1 thời điểm. Câu lệnh hay dùng để tìm tiến trình: ps aux | grep ten_tien_trinh
 -- top: Cập nhật liên tục 3 giây /lần về trạng thái CPU, RAM.
  - Các phím tắt dùng trong top: Shift+P: xem tiến trình nào tốn CPU nhất
                                 Shift+M: xem tiến trình nào tốn RAM nhất 
                                 k+số PID: kill tiến trình
 -- htop: Giống top nhưng cao cấp hơn và có màu
  - Các phím tắt trong htop: F3: search tên tiến trình                    
                             F9: kill tiến trình

--- Cách để Kill Processes:
 -- B1: tìm tên tiến trình mà cần kill: ps aux | grep ten_tien_trinh
 -- B2: Copy PID của tiến trình
 -- B3: Lệnh kill + PID 
5.Manage Software
--- Package: Là phần mềm đã được đóng gói trên linux bao gồm các file thực thi, file cấu hình, thư viện liên quan, metadata, các script cài đặt, gỡ cài đặt
    Dependencies: Là các gói phụ thuộc đề cài package, nó như là các gói hỗ trợ mà phần mềm dùng để chạy
    Conflicts: Là 2 gói không thể cài đặt được cùng nhau 
    Binary packet: là gói đã biên dịch sẵn chỉ cần cài và chạy	
--- Nén và giải nén có nhiều cách:
 -- Tar: - Nén file ta dùng lệnh tar -czvf name.tar.gz folder_name/ (c: create, z: zip, v: verbose, f: file)
         - Giải nén file ta dùng lệnh tar -xzvf folder_name/ (x: extract, z: zip, v: verbose, f: file)
 -- Zip: - Nén file: zip name.zip folder_name/
         - Giải nén file: unzip name.zip 
 -- Gzip: Chỉ nén file đơn không nén thư mục. - Nén file gzip ten_file
                                              - Giải nén gzip -d ten_file
 -- Unrar: - Nén file rar: unrar x tenfile.rar
           - Giai nen file rar: unrar d tenfile.rar
6.File System
 6.1 Cac loai File System
 --- File system duoc chia lam 4 loai chinh: 
  -- Filesystem co ban: - EXT4: Ho tro file sieu lon, hieu nang cao
                        - XFS: Xu ly duoc cac file lon va bang thong cao
                        - Btrfs: Co the Copy-on-write, snapshot, RAID
                        -
 --- fsck: Dung de quet toan bo o dia de tim cac loi du lieu, file hong, bad block va sua chung
  -- Ta chi dung fsck khi:- May khong khoi dong duoc
                          - O cung bi chuyen sang Read-only
                          - O cung bi bad
  -- Lenh co ban: fsck [option] [ten_phan_vung]. Cac option:
   - -A: Kiem tra tat ca cac filesystem
   - -C: hien thi thanh tien trinh
   - -M: Khong kiem filesystem dang mounted
   - -N: Hien thi cac thao tac da lam
   - -t: chi dinh kieu filesystem
   - -y: Tu dong dong y sua moi loi
 --- mkfs: Dung de tao ra filesystem
 6.2 Kiem tra dung luong
 --- Kiem tra dung luong ta dung 2 lenh df va du
  -- df (disk free): check xem he thong con bao nhieu dung luong trong. Cac option dung trong df: -T : hien thi loai Type(ext4,tmpfs,vfat,...)
                  -h : chuyen doi don vi block thanh GB,MB,KB 
                  -i: Hien thi Inode
                  --total: them dong total tong o cuoi 
  -- du (disk usage): check xem thu muc nay nang bao nhieu. Cac option dung trong du: -h: chuyen doi don vi thanh GB,MB,KB
      -s: Chi hien tong dung luong co trong thu muc do
      -a: hien thi tat ca cac file co trong thu muc do (mac dinh du khong co option thi chi hien dung luong cua cac thu muc)
      -c: Hien thi total tong o duoi
 --- Cac lenh quan ly file thu muc: 
  -- ls: Liet ke trong thu muc co nhung file hay thu muc con nao. Cac option: 
   -l: hien thi chi tiet (quyen, chu so huu, dung luong, ngay sua)
   -a: Hien thi tat ca cac file ke ca file an 
   -h: Hien thi dung luong duoi dang MB,GB,KB
   -R: Hien thi tat ca cac file trong tat ca cac thu muc con
  -- cp: Copy thu muc nay sang thu muc khac. Cau lenh cp [nguon][dich]. Cac option:
   - r: Bat buoc khi copy thu muc  
   - p: Giu nguyen quyen han, chu so huu
   - v: Hien thi qua trinh copy
  -- mv: Lenh doi ten hoac di chuyen. Cu phap: mv [nguon][dich]. Cac option:
   - f: ghi de khong can hoi
   - i: ghi de co hoi xac nhan
  -- rm: Xoa thu muc va file. Cu phap rm [ten_file]. Cac option:
   - r: Xoa thu muc va tat ca cac tap con trong thu muc do
   - f: Xoa ep buoc
  -- touch: tao ra 1 file rong (neu file chua ton tai). Cu phap touch [ten_file] 
6.3 Phan quyen, user dung chmod, chown
 -- chmod: Cu phap chmod + so_thu_thi + duong_dan_file, so_thuc_thi la tong cua 
read: 4, write: 2, excute: 1
 -- chown: Cu phap chown ten_nguoi_so_huu + ten_thu_muc
6.4 Cac tool de tim vi tri cua cac files
 -- find: tim vi tri file tren o cung. Cu phap: find [noi_can_tim] [option] [hanhdong]. Cac option:
  - name: tim file theo ten (phan biet chu hoa chu thuong)
  - iname: giong name nhung khong phan biet chu hoa 
  - type f: chi tim file va bo qua thu muc
  - type d: chi tim thu muc bo qua file
 -- grep: Tim noi dung trong thu muc hoac trong file. Cu phap grep [option] "tu_can_tim" [ten_file hoac thu muc]. Cac option:
  - r: de quy quet tat ca cac thu muc con
  - i: Khong phan biet chu hoa chu thuong
 -- which: Xac dinh vi tri duong dan tuyet doi cua mot file thuc thi khi no duoc khai bao trong bien moi truong $PATH. Cu phap which [option] [ten_lenh]. Cac option: 
  - a: liet ke duong dan cua tat ca cac file thuc thi trung nhau
7. Quy trinh khoi dong
--- Quy trinh khoi dong gom 4 buoc chinh:
 -- BIOS/UEFI: Buoc nay se check CPU,RAM
 -- GRUB: Buoc nay se giup ta chon he dieu hanh Linux hay Window
 -- Kernel: Phan nhan Kernel se tu chay va khoi dong chinh no 
 -- Init: He thong Init (thuong la systemd) se doc cau hinh va bat cac dich vu can thiet
--- Runlevels: Day la cac cap do van hanh. Co 5 cap do:
 -- Shutdow: tat may --> Cap do 0
 -- Single User Mode: Che do don nguoi dung: - Khong co mang 
                                             - Chi root dang nhap duoc
                                             - Co the reset mat khau root, sua loi file cau hinh
                                             --> Cap do 1
 -- Multi-user: Khong co mang --> Cap do 2
 -- Full Multi-user ( giong linux-server): - Co mang
                                           - Nhieu nguoi dung
                                           - Chi co CLI
                                           --> Cap do 3
 -- Graphical mode: -Giong het cap do 3 nhung co GUI --> Cap do 4
 -- Reboot: Khoi dong lai may
8. Quan ly he thong
    
