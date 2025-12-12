# Các lỗi thường gặp

![](images_fix/anh1.png)

CentOS 8 đã EOL (End-Of-Life) từ 2021, tất cả repo chính thức đều bị gỡ — nên dnf không thể sync repo. Fix lối:
Bước 1: Backup repo cũ
```sh
sudo mkdir /etc/yum.repos.d/backup
sudo mv /etc/yum.repos.d/*.repo /etc/yum.repos.d/backup/
```
Bước 2: Tạo repo CentOS 8 Vault mới
```sh
sudo tee /etc/yum.repos.d/CentOS-Vault.repo << 'EOF'
[baseos]
name=CentOS-8 - Base
baseurl=http://vault.centos.org/8.5.2111/BaseOS/x86_64/os/
gpgcheck=0
enabled=1

[appstream]
name=CentOS-8 - AppStream
baseurl=http://vault.centos.org/8.5.2111/AppStream/x86_64/os/
gpgcheck=0
enabled=1

[extras]
name=CentOS-8 - Extras
baseurl=http://vault.centos.org/8.5.2111/extras/x86_64/os/
gpgcheck=0
enabled=1
EOF
```
Bước 3: Clean cache và update 
```sh
sudo dnf clean all
sudo dnf makecache
sudo dnf update -y
```
Bước 4: Cài lại python
```sh
sudo dnf install -y python3 python3-pip git
```

