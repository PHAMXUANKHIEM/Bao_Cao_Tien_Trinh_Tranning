# Triển khai cụm Ceph (ceph-deploy)
## Chuẩn bị 

![](/home/xuankhiem/Bao_Cao/Bao_Cao_Tien_Trinh_Tranning/Ceph/imgaes/anh2.png)

## Cấu hình cài đặt 
 ### Cài đặt môi trường: 
 Ceph-deploy không còn hỗ trợ CentOS 8 kể từ Ceph Nautilus trở lên, vì RedHat chuyển sang CentOS Stream → khiến ceph-deploy bỏ luôn hỗ trợ do xung đột Python + repo. Ta phải cài python3+pip3 để ceph-deploy hỗ trợ
-Trên tất cả các node:
```sh
   dnf install -y python3 python3-pip git
```
-Clone ceph-deploy từ GitHub
```sh
   git clone https://github.com/ceph/ceph-deploy.git
   cd ceph-deploy
   pip3 install .
```
-Cài đặt chrony trên tất cả các node để đồng bộ thời gian
```sh
   yum install chrony -y
```
-Trên tất cả các node thêm cấu hình file /etc/host:
```sh
   10.2.1.54 ceph1
   10.2.1.81 ceph2     
   10.2.1.83 ceph3
```
-Tạo người dùng Ceph trên tất cả các node:
```sh
   useradd -d /home/ceph -m ceph
   passwd ceph 
```
-Thêm quyền:
```sh
  echo "ceph ALL = (root) NOPASSWD:ALL" | sudo tee /etc/sudoers.d/ceph
  sudo chmod 0440 /etc/sudoers.d/ceph
```
-Đăng nhập bằng user ceph:
```sh
  su ceph
```
-Trên ceph1 tạo ssh-keygen
```sh
   ssh-keygen 
   ssh-copy-id ceph@ceph2
   ssh-copy-id ceph@ceph3
```
-Tắt SElinux
```sh
 sudo setenforce 0
 ```
-Tạo thư mục cluster trên ceph1:
```sh
 mkdir ~/ceph-cluster
 cd ~/ceph-cluster
```
### Chuẩn bị repo để tải
Trên tất cả các node
-Disable module mặc định của CentOS 8
```sh
  sudo dnf module disable -y container-tools
  sudo dnf module disable -y python36
  sudo dnf module disable -y python38
  sudo dnf module disable -y firewall
```
-Tạo repo Ceph thủ công
```sh
  sudo vi /etc/yum.repos.d/ceph.repo
```
```sh
  [ceph]
  name=Ceph Octopus
  baseurl=https://download.ceph.com/rpm-octopus/el8/x86_64/
  enabled=1
  gpgcheck=0

  [ceph-noarch]
  name=Ceph noarch
  baseurl=https://download.ceph.com/rpm-octopus/el8/noarch/
  enabled=1
  gpgcheck=0

  [ceph-source]
  name=Ceph Source
  baseurl=https://download.ceph.com/rpm-octopus/el8/SRPMS/
  enabled=0
  gpgcheck=0
```
-Cài dependency bắt buộc cho Ceph trên el8
```sh
      sudo dnf install -y epel-release
      sudo dnf install -y python3 python3-pip python3-setuptools \
      lvm2 chrony smartmontools hdparm \
      wget curl git jq
```
-Cài Ceph package thủ công  
```sh
      sudo dnf install -y ceph ceph-mon ceph-mgr ceph-osd ceph-mds ceph-radosgw
```
-Fake file /etc/redhat-release thành CentOS 7
```sh
    sudo cp /etc/redhat-release /etc/redhat-release.bak
    echo "CentOS Linux release 7.9.2009 (Core)" | sudo tee /etc/redhat-release
```
Trên ceph2 và ceph3 tạo thư mục cho OSD 
```sh
   sudo mkdir -p /var/local/osd0
   sudo chown ceph:ceph /var/local/osd0
```
Trên ceph1 khởi tạo cụm
```sh
    ceph-deploy new ceph1 ceph2 ceph3
```
Tạo OSD trên Ceph
- Kiểm tra ổ cứng trống 
```sh
  lsblk
```
- Làm sạch phân vùng
```sh
  sudo sgdisk --zap-all /dev/vdb
```
- Add OSD
```sh
 ceph-deploy osd create ceph1 --data /dev/vdb
 ceph-deploy osd create ceph2 --data /dev/vdb
 ceph-deploy osd create ceph3 --data /dev/vdb
 ```
 -Check trạng thái
 ```sh
  ceph -s
 ```
![](/home/xuankhiem/Bao_Cao/Bao_Cao_Tien_Trinh_Tranning/Ceph/imgaes/anh1.png)

 -Khi out user ceph ra vao lai phai nhap lenh 
 ```sh
 export PATH=$PATH:/usr/local/bin
 ```