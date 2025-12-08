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

![](images_file_system/anh1.png)

 ## 3. Tạo filesystem (`mkfs`)

```sh
mkfs.ext4 /dev/sdb1
mkfs.xfs /dev/sdb1
```
![](images_file_system/anh2.png)

 ## 4. Kiểm tra dung lượng: `df` và `du`

 - `df` (disk free): xem dung lượng trống của các phân vùng.
 - `du` (disk usage): xem dung lượng sử dụng trong thư mục.

![](images_file_system/anh3.png)

![](images_file_system/anh4.png)


 Ví dụ:

 ```sh
 df -h        # hiển thị theo định dạng dễ đọc (GB/MB)
 df -hT       # thêm cột kiểu filesystem
 df -i        # hiển thị inode

 du -h        # xem dung lượng của thư mục hiện tại
 du -sh /var  # tổng dung lượng /var dưới dạng dễ đọc
 du -ah       # liệt kê dung lượng tất cả file và thư mục
 ```
![](images_file_system/anh5.png)

 