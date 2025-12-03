# Triển khai OpenStack
## 1. Chuẩn bị môi trường
- Cài đặt hệ điều hành Ubuntu Server 22.04 trên tất cả các nút
Mô hình triển khai:
- Controller Node: Quản lý các dịch vụ OpenStack
- Compute Node: Chạy các máy ảo

![](images/deloy_openstack/anh1.png)

  ### Cập nhật hệ thống:
  ```sh
    sudo apt update && sudo apt upgrade -y
  ```
  ### Cấu hình hostname và file hosts:
  -Trên Controller Node:
  ```sh
    sudo nano /etc/hosts
  ```
  ```sh
    192.168.1.76 controller
    192.168.1.53 compute
  ```
  -Ping để kiểm tra kết nối giữa các nút:
  ```sh
    ping compute #Trên controller
  ``` 
  ### Cài đặt NTP để đồng bộ thời gian:
  ```sh
    sudo apt install chrony -y
  ```   
  ### Cấu hình NTP trên tất cả các nút:
  -Trên Controller Node:
  ```sh
    sudo nano /etc/chrony/chrony.conf
  ```
  ```sh
    server  0.vn.pool.ntp.org iburst #Máy chủ NTP công cộng
    allow 192.168.1.0/24 #Cho phép mạng nội bộ đồng bộ thời gian
  ```
  -Trên Compute Node:
  ```sh
    sudo nano /etc/chrony/chrony.conf
  ```
  ```sh
    server controller iburst #Đồng bộ thời gian từ Controller Node
  ```
  ### Khởi động lại dịch vụ Chrony:
  ```sh
    sudo systemctl restart chrony
    sudo systemctl enable chrony
  ```
  ### Kiểm tra đồng bộ thời gian:
  ```sh
    chronyc sources
  ``` 
  ![](images/deloy_openstack/anh2.png)
  ### Cài đặt OpenStack Repository và Openstack Client:
  Ở đây sử dụng phiên bản Zed:
  ```sh
      sudo add-apt-repository cloud-archive:zed -y
      sudo apt update && sudo apt upgrade -y
  ```
  ```sh
      sudo apt install python3-openstackclient -y
  ```
  ### Cài đặt SQL Database (MariaDB):
  -Trên Controller Node:
  ```sh
    sudo apt install mariadb-server python3-pymysql -y
  ```
  -Cấu hình MariaDB:
  ```sh
    sudo nano /etc/mysql/mariadb.conf.d/99-openstack.cnf
  ```
  ```sh
    [mysqld]
      bind-address = 192.168.1.76
      default-storage-engine = innodb
      innodb_file_per_table = on
      max_connections = 4096
      collation-server = utf8_general_ci
      character-set-server = utf8
  ```
  -Khởi động lại dịch vụ MariaDB:
  ```sh
    sudo systemctl restart mariadb
    sudo systemctl enable mariadb
  ```
  ### Cài đặt và cấu hình RabbitMQ (Message Broker để các dịch vụ OpenStack giao tiếp với nhau):
  -Trên Controller Node:
  ```sh
    sudo apt install rabbitmq-server -y
  ```
  -Tạo người dùng RabbitMQ cho OpenStack và cho phép quyền truy cập cần thiết:
  ```sh
    sudo rabbitmqctl add_user openstack RABBIT_PASS #Tạo user mới (thay RABBIT_PASS bằng mật khẩu mạnh)
    sudo rabbitmqctl set_permissions openstack ".*" ".*" ".*" #Cấp quyền cho user
  ```

![](images/deloy_openstack/anh3.png)

  ### Cài đặt và cấu hình Memcached (Để lưu trữ cache cho các dịch vụ OpenStack):
  -Trên Controller Node:
  ```sh
    sudo apt install memcached python3-memcache -y
  ```
  -Cấu hình Memcached:
  ```sh
    sudo nano /etc/sysconfig/memcached
  ```
  ```sh
    OPTIONS="-l 127.0.0.1
  
  ### Tắt UFW trên tất cả các nút (nếu đang bật):
  ```sh
    sudo ufw disable
  ```
  