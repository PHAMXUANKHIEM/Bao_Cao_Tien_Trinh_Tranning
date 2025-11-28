 - sh: bản tiêu chuẩn chạy script trên hệ thống Unix
 - bash: nâng cao của sh có nhiều tính năng hơn và chạy chủ yếu trên Linux
 - csh: tương tự như sh và có nhiều tính năng hơn 
 - ksh : một trong những shell phổ biến nhất trên các hệ thống UNIX hỗ trợ cho biến mảng (array variables) cú pháp lặp for cải tiến 
 - Standard input (STDIN): là luồng dữ liệu đầu vào của chương trình lấy mặc định từ bàn phím. VD: lệnh cat < file.txt sẽ chuyển hướng lệnh cat tới thư mục file.txt
 - Standard output (STDOUT): là luồng dữ liệu đầu ra chuẩn, chương trình sẽ ghi kết quả vào đây và hiển thị lên terminal
 - Standard error (STDERR): là thông báo lỗi khi chương trình gửi lỗi và cũng mặc định hiển thị trên terminal
 - Piping: dùng dấu | là cách lấy stdout của chương trình A và dùng nó làm STDIN của chương trình B. VD (ip a | grep ens32) là nó sẽ chỉ hiển thị ra ens32 
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
 -- paste: Kết hợp 2 file theo hàng ngang và không dựa trên khóa. Các ví dụ câu lệnh paste và các option quan trọng gồm:- Ghép file: paste [option] file1.txt file2.txt
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
 -- head: Đọc file ở đâu, mặc định là 10 dòng, option -n dùng để 
 # Linux cơ bản

 Tài liệu tóm tắt các kiến thức cơ bản về Linux: shell, thao tác thư mục, luồng I/O và một số lệnh thường dùng.

 ## Shell

 - **sh**: bản tiêu chuẩn chạy script trên hệ thống Unix.
 - **bash**: nâng cấp của `sh`, có nhiều tính năng hơn, phổ biến trên Linux.
 - **csh**: shell kiểu C, có cú pháp khác.
 - **ksh**: phổ biến trên UNIX, hỗ trợ mảng và cú pháp lặp nâng cao.

 ## Thao tác thư mục

 - Thay đổi thư mục: `cd <thư_mục>`
 - Xem thư mục hiện tại: `pwd`

 ## Lịch sử lệnh

 - Xem lịch sử: `history`
 - Dùng phím lên/xuống để chọn lại lệnh trước đó.

 ## Biến môi trường

 - Gán biến: `export TEN_BIEN="gia_tri_gan"`
 - Xem biến: `echo $TEN_BIEN`
 - Xem tất cả biến: `env`

 ## Trang hướng dẫn (man)

 - Xem hướng dẫn chi tiết: `man <ten_lenh>` (ví dụ `man ls`).

 ## Luồng dữ liệu: STDIN / STDOUT / STDERR

 - **STDIN**: luồng vào (mặc định là bàn phím). Ví dụ: `cat < file.txt`.
 - **STDOUT**: luồng ra chuẩn, hiện trên terminal.
 - **STDERR**: luồng lỗi, cũng hiện trên terminal.
 - **Piping**: dùng `|` để lấy `STDOUT` của chương trình này làm `STDIN` của chương trình khác. Ví dụ: `ip a | grep ens32`.

 ## Một số lệnh quan trọng

 ### cat

 Dùng để xem, ghép hoặc tạo file.

 ```sh
 cat file.txt            # xem file
 cat file.txt file1.txt >> output.txt  # ghép file
 cat > newfile.txt       # tạo file nhanh
 ```

 Các option hữu ích:

 - `-n`: đánh số dòng (kể cả dòng trống)
 - `-b`: đánh số dòng không rỗng
 - `-A`: hiển thị ký tự đặc biệt
 - `-s`: xóa dòng trống lặp

 ### join

 Ghép hai file theo cột khóa chung (file phải được sắp xếp trước).

 ```sh
 join file1.txt file2.txt
 ```

 Option thường dùng:

 - `-a N`: in toàn bộ dữ liệu của file N (1 hoặc 2)
 - `-v N`: in dữ liệu không khớp của file N
 - `-t CHAR`: chỉ định dấu phân cách (ví dụ CSV)
 - `-o`: chỉ định cột xuất ra
 - `-e`: điền giá trị cho ô trống

 ### paste

 Ghép hai file theo cột ngang (không dựa trên khóa).

 ```sh
 paste file1.txt file2.txt
 ```

 Option:

 - `-d SEPARATOR`: thay đổi dấu phân cách
 - `-s`: ghép các dòng của một file thành hàng ngang

 ### tac

 Đọc file từ dưới lên (ngược với `cat`), hữu ích khi xem log:

 ```sh
 tac /var/log/syslog | head -n 10
 ```

 ### sort

  Sắp xếp văn bản.

 ```sh
 sort file.txt
 sort -n file.txt     # sắp xếp theo số
 sort -r file.txt     # đảo ngược
 sort -k 2 -t ',' file.csv  # sắp theo cột 2 với dấu phẩy
 ```

 ### uniq

 Lọc trùng lặp (thường dùng sau `sort`).

 ```sh
 sort file.txt | uniq
 sort file.txt | uniq -c   # đếm số lần xuất hiện
 ```

 Option:

 - `-c`: đếm số lần xuất hiện
 - `-d`: chỉ in dòng trùng
 - `-u`: chỉ in dòng không trùng

 ### split

 Chia file lớn thành các file nhỏ:

 ```sh
 split -l 1000 bigfile.txt   # chia theo 1000 dòng
 split -b 10M bigfile.txt    # chia theo kích thước
 split -d -l 1000 bigfile.txt prefix_  # dùng số làm hậu tố
 ```

 ### head

 Xem đầu file (mặc định 10 dòng):

 ```sh
 head file.txt
 head -n 20 file.txt   # xem 20 dòng đầu
 ```