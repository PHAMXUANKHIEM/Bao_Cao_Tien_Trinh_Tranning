 # File system

 Tổng quan về quản lý file hệ thống: loại filesystem, kiểm tra/khởi tạo filesystem, kiểm tra dung lượng, các lệnh quản lý file/thư mục và công cụ tìm kiếm.

 ## 1. Các loại filesystem

 - **EXT4**: phổ biến, hỗ trợ file lớn, hiệu năng tốt.
 - **XFS**: xử lý tốt file lớn và hệ thống có băng thông cao.
 - **Btrfs**: hỗ trợ copy-on-write, snapshot, RAID.
 - Các loại khác: `tmpfs`, `vfat`, `ntfs`, ...

 ## 2. Kiểm tra và sửa filesystem (`fsck`)

 `fsck` dùng để quét và sửa lỗi filesystem.

 Khi dùng `fsck`:

 - Chỉ chạy trên phân vùng không `mounted` (hoặc ở chế độ cứu hộ).
 - Dùng khi máy không khởi động, phân vùng bị chuyển sang `read-only` hoặc có bad blocks.

 Ví dụ và các option phổ biến:

 ```sh
 fsck -A        # kiểm tra tất cả các filesystem trong /etc/fstab
 fsck -C        # hiển thị thanh tiến trình
 fsck -M        # bỏ qua filesystem đang mounted
 fsck -N        # show các thao tác sẽ làm (không thực hiện)
 fsck -t ext4 /dev/sda1  # chỉ định kiểu filesystem
 fsck -y /dev/sda1      # tự động đồng ý sửa lỗi
 ```

 ## 3. Tạo filesystem (`mkfs`)

```sh
mkfs.ext4 /dev/sdb1
mkfs.xfs /dev/sdb1
```

 ## 4. Kiểm tra dung lượng: `df` và `du`

 - `df` (disk free): xem dung lượng trống của các phân vùng.
 - `du` (disk usage): xem dung lượng sử dụng trong thư mục.

 Ví dụ:

 ```sh
 df -h        # hiển thị theo định dạng dễ đọc (GB/MB)
 df -hT       # thêm cột kiểu filesystem
 df -i        # hiển thị inode

 du -h        # xem dung lượng của thư mục hiện tại
 du -sh /var  # tổng dung lượng /var dưới dạng dễ đọc
 du -ah       # liệt kê dung lượng tất cả file và thư mục
 ```

 ## 5. Các lệnh quản lý file và thư mục

 - `ls` — liệt kê file/thư mục

 ```sh
 ls -l     # chi tiết (quyền, chủ sở hữu, kích thước, ngày sửa)
 ls -a     # hiện cả file ẩn
 ls -h     # kích thước dạng đọc được
 ls -R     # đệ quy liệt kê thư mục con
 ```

 - `cp` — sao chép file/thư mục

 ```sh
 cp file.txt /path/to/dest/            # copy file
 cp -r dir1/ dir2/                     # copy thư mục
 cp -p file file.bak                   # giữ quyền và chủ sở hữu
 ```

 - `mv` — di chuyển hoặc đổi tên

 ```sh
 mv oldname newname
 mv file /path/to/destination/
 ```

 - `rm` — xóa file/thư mục (cẩn thận)

 ```sh
 rm file.txt
 rm -r somedir/    # xóa thư mục và nội dung
 rm -f file.txt    # xóa ép buộc
 ```

 - `touch` — tạo file rỗng hoặc cập nhật thời gian sửa đổi

 ```sh
 touch newfile.txt
 ```

 ## 6. Phân quyền và sở hữu

 - `chmod` — thay đổi quyền truy cập (r=4, w=2, x=1)

 ```sh
 chmod 644 file.txt   # rw-r--r--
 chmod +x script.sh    # thêm quyền thực thi
 ```

 - `chown` — thay đổi chủ sở hữu

 ```sh
 chown user:group file.txt
 ```

 ## 7. Công cụ tìm kiếm file và nội dung

 - `find` — tìm file theo tên, loại, thời gian, v.v.

 ```sh
 find / -name "*.log"        # tìm tất cả file .log
 find . -type d -name "tmp"  # tìm thư mục tên tmp
 ```

 - `grep` — tìm nội dung trong file

 ```sh
 grep -R "TODO" .            # tìm chữ TODO trong thư mục hiện tại (đệ quy)
 grep -i "error" /var/log/syslog
 ```

 - `which` — xác định đường dẫn thực thi của lệnh trong `$PATH`

 ```sh
 which python3
 which -a python3   # liệt kê tất cả kết quả trùng
 ```
