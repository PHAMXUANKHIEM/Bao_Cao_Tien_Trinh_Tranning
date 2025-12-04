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
    sudo nano /etc/memcached.conf
  ```
  ```sh
    -l 127.0.0.1,192.168.1.76
  ```
  -Khởi động lại dịch vụ Memcached:
  ```sh
    sudo systemctl restart memcached
    sudo systemctl enable memcached
  ```
  ### Tắt UFW trên tất cả các nút (nếu đang bật):
  ```sh
    sudo ufw disable
  ```
## 2. Cấu hình OpenStack Identity Service (Keystone)
-Trên Controller Node:
  ###  Tạo biến môi trường cho admin:
  -Tạo file `admin-openrc.sh` để lưu thông tin xác thực:
  ```sh
    nano admin-openrc.sh
  ```
  -Nội dung file: 
  ```sh
      export OS_USERNAME=admin
      export OS_PASSWORD=ADMIN_PASS #Thay ADMIN_PASS bằng mật khẩu mạnh
      export OS_PROJECT_NAME=admin
      export OS_USER_DOMAIN_NAME=Default
      export OS_PROJECT_DOMAIN_NAME=Default
      export OS_AUTH_URL=http://controller:35357/v3
      export OS_IDENTITY_API_VERSION=3
  ``` 
  -Nguồn file để sử dụng thông tin xác thực:
  ```sh
      source admin-openrc.sh
  ```
  ### Tạo Database cho Keystone:
  -Trên Controller Node kết nối vào MariaDB bằng root:
  ```sh
    sudo mysql -u root -p
  ```
  -Tạo database và người dùng cho Keystone:
  ```sql
    MariaDB [(none)]> CREATE DATABASE keystone;
    Grant proper access to the keystone database:
    MariaDB [(none)]> GRANT ALL PRIVILEGES ON keystone.* TO 'keystone'@'localhost' \ 
    IDENTIFIED BY '123123Aa';
    MariaDB [(none)]> GRANT ALL PRIVILEGES ON keystone.* TO 'keystone'@'%' \
    IDENTIFIED BY '123123Aa';
  ```
  ### Cài đặt Keystone:
  -Trên Controller Node:
  ```sh
    sudo apt install keystone apache2 libapache2-mod-wsgi-py3 -y
  ```
  -Sửa file cấu hình Keystone:
  ```sh
    sudo nano /etc/keystone/keystone.conf
  ```
  -Cấu hình database trong file `keystone.conf`:
  ```sh
    [database]
    connection = mysql+pymysql://keystone:123123Aa@controller/keystone
  ```
  -Cấu hình token trong file `keystone.conf`:
  ```sh
    [token]
    provider = fernet
  ``` 
  -Tạo database cho dịch vụ xác thực:
  ```sh
    su -s /bin/sh -c "keystone-manage db_sync" keystone
  ```
  -Tạo khoá Fernet và các khoá mã hoá:
  ```sh
    keystone-manage fernet_setup --keystone-user keystone --keystone-group keystone
    keystone-manage credential_setup --keystone-user keystone --keystone-group keystone
  ```
  -Bootstrap Keystone để tạo dịch vụ ban đầu và tài khoản admin:
  ```sh
    keystone-manage bootstrap \                                                
    --bootstrap-password ADMIN_PASS \                                                                   
    --bootstrap-admin-url http://controller:5000/v3/ \                                                    
    --bootstrap-internal-url http://controller:5000/v3/ \                                               
    --bootstrap-public-url http://controller:5000/v3/ \                                                 
    --bootstrap-region-id RegionOne 
  ``` 
  -Kiểm tra cài đặt Keystone:
  ```sh
    openstack service list
  ```
  ![](images/deloy_openstack/anh4.png)
  ### Cài đặt Glance:
   -Trên Controller Node tạo database cho Glance:
  ```sh
    sudo mysql -u root -p
  ```
  ```sql
    MariaDB [(none)]> CREATE DATABASE glance;
    Grant proper access to the glance database:
    MariaDB [(none)]> GRANT ALL PRIVILEGES ON glance.* TO 'glance'@'localhost' \ 
    IDENTIFIED BY 'GLANCE_DBPASS';
    MariaDB [(none)]> GRANT ALL PRIVILEGES ON glance.* TO 'glance'@'%' \
    IDENTIFIED BY 'GLANCE_DBPASS';
  ```
  -Vào lại môi trường admin:
  ```sh
    source admin-openrc.sh
  ``` 
  -Tạo người dùng, vai trò, dịch vụ và endpoint cho Glance:
  ```sh
    openstack user create --domain default --password GLANCE_PASSWORD glance
    openstack role add --project service --user glance admin
    openstack service create --name glance --description "OpenStack Image" image
    openstack endpoint create --region RegionOne image public http://controller:9292
    openstack endpoint create --region RegionOne image internal http://controller:9292
    openstack endpoint create --region RegionOne image admin http://controller:9292
  ``` 
  ![](images/deloy_openstack/anh5.png)

  -Cài đặt Glance:
  -Trên Controller Node:
  ```sh
    sudo apt install glance -y
  ```
  -Sửa file cấu hình Glance:
  ```sh
    sudo nano /etc/glance/glance-api.conf
  ```
  -Cấu hình database trong file `glance-api.conf`:
  ```sh
      [database]
      connection = mysql+pymysql://glance:GLANCE_DBPASS@controller/glance

      [keystone_authtoken]
      www_authenticate_uri  = http://controller:5000
      auth_url = http://controller:5000
      memcached_servers = controller:11211
      auth_type = password 
      project_domain_name = Default
      user_domain_name = Default
      project_name = service
      username = glance
      password = GLANCE_PASS

      [paste_deploy]
      # ...
      flavor = keystone

      [glance_store]
      # ...
      stores = file,http
      default_store = file
      filesystem_store_datadir = /var/lib/glance/images/
  ```
  ```sh
    su -s /bin/sh -c "glance-manage db_sync" glance
  ```
  -Khởi động lại dịch vụ Glance:
  ```sh
    sudo systemctl restart glance-api
    sudo systemctl enable glance-api
  ``` 
  ### Cài đặt Placement
  -Trên Controller Node tạo database cho Placement:
  ```sh
    sudo mysql -u root -p
  ```
  ```sql
    DROP DATABASE IF EXISTS placement;
    CREATE DATABASE IF NOT EXISTS placement;
    GRANT ALL PRIVILEGES ON placement.* TO 'placement'@'localhost' \
    IDENTIFIED BY 'PLACEMENT_DBPASS'; 
    GRANT ALL PRIVILEGES ON placement.* TO 'placement'@'%' \
    IDENTIFIED BY 'PLACEMENT_DBPASS';
  ```
  -Vào lại môi trường admin:
  ```sh
    source admin-openrc.sh
  ``` 
  -Tạo người dùng, vai trò, dịch vụ và endpoint cho Placement:
  ```sh
    openstack user create --domain default --password PLACEMENT_PASS placement
    openstack role add --project service --user placement admin
    openstack service create --name placement --description "OpenStack Placement" placement
    openstack endpoint create --region RegionOne placement public http://controller:8778
    openstack endpoint create --region RegionOne placement internal http://controller:8778
    openstack endpoint create --region RegionOne placement admin http://controller:8778
  ``` 
  ![](images/deloy_openstack/anh7.png)

  -Cài đặt Placement:
  -Trên Controller Node:
  ```sh
    sudo apt install placement-api -y
  ``` 
  -Sửa file cấu hình Placement:
  ```sh
    sudo nano /etc/placement/placement.conf
  ```
  -Cấu hình database trong file `placement.conf`:
  ```sh
      [database]
      connection = mysql+pymysql://placement:PLACEMENT_DBPASS@controller/placement  
      [keystone_authtoken]
      www_authenticate_uri = http://controller:5000
      auth_url = http://controller:5000
      memcached_servers = controller:11211
      auth_type = password
      project_domain_name = Default
      user_domain_name = Default
      project_name = service
      username = placement
      password = PLACEMENT_PASS
  ```
  ```sh
    su -s /bin/sh -c "placement-manage db sync" placement
  ```
  -Khởi động lại dịch vụ Placement:
  ```sh
    sudo systemctl restart apache2
    sudo systemctl enable apache2
  ```
  ### Cài đặt Nova
  -Trên Controller Node tạo database cho Nova:
  ```sh
    sudo mysql -u root -p
  ```
  ```sql
    CREATE DATABASE nova_api;
    CREATE DATABASE nova;
    CREATE DATABASE nova_cell0;

    GRANT ALL PRIVILEGES ON nova_api.* TO 'nova'@'localhost' \
      IDENTIFIED BY 'NOVA_DBPASS';
    GRANT ALL PRIVILEGES ON nova_api.* TO 'nova'@'%' \
      IDENTIFIED BY 'NOVA_DBPASS';
    GRANT ALL PRIVILEGES ON nova.* TO 'nova'@'localhost' \
      IDENTIFIED BY 'NOVA_DBPASS';
    GRANT ALL PRIVILEGES ON nova.* TO 'nova'@'%' \
      IDENTIFIED BY 'NOVA_DBPASS';
    GRANT ALL PRIVILEGES ON nova_cell0.* TO 'nova'@'localhost' \
      IDENTIFIED BY 'NOVA_DBPASS';
    GRANT ALL PRIVILEGES ON nova_cell0.* TO 'nova'@'%' \
      IDENTIFIED BY 'NOVA_DBPASS';
  ```
  -Vào lại môi trường admin:
  ```sh
    source admin-openrc.sh
  ```
  -Tạo người dùng, vai trò, dịch vụ và endpoint cho Nova:
  ```sh
    openstack user create --domain default --password NOVA_PASS nova
    openstack role add --project service --user nova admin
    openstack service create --name nova --description "OpenStack Compute" compute
    openstack endpoint create --region RegionOne compute public http://controller:8774/v2.1
    openstack endpoint create --region RegionOne compute internal http://controller:8774/v2.1
    openstack endpoint create --region RegionOne compute admin http://controller:8774/v2.1
  ``` 
  ![](images/deloy_openstack/anh6.png)

  -Cài đặt Nova:
  -Trên Controller Node:
  ```sh
    sudo apt install nova-api nova-conductor nova-novncproxy nova-scheduler -y
  ```
  -Sửa file cấu hình Nova:
  ```sh
    sudo nano /etc/nova/nova.conf
  ```
  -Cấu hình database trong file `nova.conf`:
  ```sh
      [database]
      connection = mysql+pymysql://nova:NOVA_DBPASS@controller/nova
      [api_database]
      connection = mysql+pymysql://nova:NOVA_DBPASS@controller/nova_api
      [api]
      auth_strategy = keystone
      [keystone_authtoken]
      www_authenticate_uri = http://controller:5000/
      auth_url = http://controller:5000/
      memcached_servers = controller:11211
      auth_type = password
      project_domain_name = Default
      user_domain_name = Default
      project_name = service
      username = nova
      password = NOVA_PASS
      [placement]
      region_name = RegionOne
      project_domain_name = Default
      project_name = service
      auth_type = password
      user_domain_name = Default
      auth_url = http://controller:5000/v3
      username = placement
      password = PLACEMENT_PASS
      [vnc]
      enabled = true
      server_listen = $my_ip
      server_proxyclient_address = $my_ip
      [DEFAULT]
      transport_url = rabbit://openstack:RABBIT_PASS@controller:5672/
      myip = 192.168.1.76
      [service_user]
      send_service_user_token = true
      auth_url = https://controller/identity
      auth_strategy = keystone
      auth_type = password
      project_domain_name = Default
      project_name = service
      user_domain_name = Default
      username = nova
      password = NOVA_PASS
      [glance]
      api_servers = http://controller:9292
      [oslo_concurrency]
      lock_path = /var/lib/nova/tmp
  ```
  -Dồng bộ database:
  ```sh
      su -s /bin/sh -c "nova-manage api_db sync" nova

      su -s /bin/sh -c "nova-manage cell_v2 map_cell0" nova

      su -s /bin/sh -c "nova-manage cell_v2 create_cell --name=cell1 --verbose" nova

      su -s /bin/sh -c "nova-manage db sync" nova

      su -s /bin/sh -c "nova-manage cell_v2 list_cells" nova
  ```
  ![](images/deloy_openstack/anh8.png)

  -Khởi động lại dịch vụ Nova:
  ```sh
    sudo systemctl restart nova-api nova-scheduler nova-conductor nova-novncproxy
    sudo systemctl enable nova-api nova-scheduler nova-conductor nova-novncproxy
  ```
  -Trên Compute Node:
  ```sh
    sudo apt install nova-compute -y
  ```
  -Sửa file cấu hình Nova trên Compute Node:
  ```sh
    sudo nano /etc/nova/nova.conf
  ```
  -Cấu hình file `nova.conf` trên Compute Node:
  ```sh
      [DEFAULT]
      transport_url = rabbit://openstack:RABBIT_PASS@controller:5672/
      my_ip = 192.168.1.53
      use_neutron = true
      firewall_driver = nova.virt.firewall.NoopFirewallDriver
      [keystone_authtoken]
      www_authenticate_uri = http://controller:5000/
      auth_url = http://controller:5000/
      memcached_servers = controller:11211
      auth_type = password
      project_domain_name = Default
      user_domain_name = Default
      project_name = service
      username = nova
      password = NOVA_PASS
      [placement]
      region_name = RegionOne
      project_domain_name = Default
      project_name = service
      auth_type = password
      user_domain_name = Default
      auth_url = http://controller:5000/v3
      username = placement
      password = PLACEMENT_PASS
      [libvirt]
      virt_type = qemu
      [oslo_concurrency]
      lock_path = /var/lib/nova/tmp
      [glance]    
      api_servers = http://controller:9292
      [vnc]
      enabled = true
      server_listen = $my_ip
      server_proxyclient_address = $my_ip
      novncproxy_base_url = http://controller:6080/vnc_auto.html
      [api]
      auth_strategy = keystone
  ```
  -Khởi động lại dịch vụ Nova trên Compute Node:
  ```sh
    sudo systemctl restart nova-compute
    sudo systemctl enable nova-compute
  ```
  ### Cài đặt Neutron
  -Trên Controller Node tạo database cho Neutron:
  ```sh
    sudo mysql -u root -p
  ```
  ```sql
    CREATE DATABASE neutron;
    GRANT ALL PRIVILEGES ON neutron.* TO 'neutron'@'localhost' \
      IDENTIFIED BY 'NEUTRON_DBPASS';
    GRANT ALL PRIVILEGES ON neutron.* TO 'neutron'@'%' \
      IDENTIFIED BY 'NEUTRON_DBPASS';
  ```
  -Vào lại môi trường admin:
  ```sh
    source admin-openrc.sh
  ``` 
  -Tạo người dùng, vai trò, dịch vụ và endpoint cho Neutron:
  ```sh 
    openstack user create --domain default --password NEUTRON_PASS neutron
    openstack role add --project service --user neutron admin
    openstack service create --name neutron --description "OpenStack Networking" network
    openstack endpoint create --region RegionOne network public http://controller:9696
    openstack endpoint create --region RegionOne network internal http://controller:9696
    openstack endpoint create --region RegionOne network admin http://controller:9696
  ```
  ![](images/deloy_openstack/anh9.png)

  -Cài đặt Neutron (Cài theo Provider Network với Open vSwitch):
  -Trên Controller Node:
  ```sh
    sudo apt install neutron-server neutron-plugin-ml2 neutron-openvswitch-agent neutron-l3-agent neutron-dhcp-agent neutron-metadata-agent -y
  ```
  -Tạo bridge br-ex trên Controller Node:
  ```sh
    sudo ovs-vsctl add-br br-ex
    sudo ovs-vsctl add-port br-ex enp0s8  #Thay enp0s8 bằng tên interface kết nối mạng ngoài
  ```

![](images/deloy_openstack/anh10.png)

  -Sửa file cấu hình Neutron:
  ```sh
    sudo nano /etc/neutron/neutron.conf
  ```
  -Cấu hình file `neutron.conf`:
  ```sh
      [database]
      connection = mysql+pymysql://neutron:NEUTRON_DBPASS@controller/neutron
      [DEFAULT] 
      core_plugin = ml2
      service_plugins = 
      transport_url = rabbit://openstack:RABBIT_PASS@controller
      auth_strategy = keystone
      notify_nova_on_port_status_changes = true
      notify_nova_on_port_data_changes = true
      [keystone_authtoken]
      www_authenticate_uri = http://controller:5000
      auth_url = http://controller:5000
      memcached_servers = controller:11211
      auth_type = password
      project_domain_name = Default
      user_domain_name = Default
      project_name = service
      username = neutron
      password = NEUTRON_PASS
      [nova]
      auth_url = http://controller:5000
      auth_type = password
      project_domain_name = Default
      user_domain_name = Default
      region_name = RegionOne
      project_name = service
      username = nova
      password = NOVA_PASS
      [oslo_concurrency]
      lock_path = /var/lib/neutron/tmp
  ```
  -Cấu hình ML2:
  ```sh
    sudo nano /etc/neutron/plugins/ml2/ml2_conf.ini 
  ```
  -Cấu hình file `ml2_conf.ini`:
  ```sh
      [ml2]
      type_drivers = flat,vlan,vxlan
      tenant_network_types = 
      mechanism_drivers = openvswitch
      extension_drivers = port_security
      [ml2_type_flat]
      flat_networks = provider
  ``` 
  -Cấu hình Open vSwitch Agent:
  ```sh
    sudo nano /etc/neutron/plugins/ml2/openvswitch_agent.ini
  ```
  -Cấu hình file `openvswitch_agent.ini`:
  ```sh
      [ovs]
      bridge_mappings = provider:br-ex
      [securitygroup]
      enable_security_group = true
      firewall_driver = openvswitch
      #firewall_driver = iptables_hybrid
  ```
  -Cấu hình DHCP Agent:
  ```sh
    sudo nano /etc/neutron/dhcp_agent.ini
  ```
  -Cấu hình file `dhcp_agent.ini`:
  ```sh
      [DEFAULT]
      dhcp_driver = neutron.agent.linux.dhcp.Dnsmasq
      enable_isolated_metadata = true
  ```
  -Cấu hình metadata_agent:
  ```sh
    sudo nano /etc/neutron/metadata_agent.ini
  ```
  -Cấu hình file `metadata_agent.ini`:
  ```sh
      [DEFAULT]
      nova_metadata_host = controller
      metadata_proxy_shared_secret = METADATA_SECRET
  ```
  -Cấu hình Nova: 
  ```sh
    sudo nano /etc/nova/nova.conf
  ```
  -Thêm cấu hình Neutron vào file `nova.conf`:
  ```sh
      [neutron]
      auth_url = http://controller:5000
      auth_type = password
      project_domain_name = Default
      user_domain_name = Default
      region_name = RegionOne
      project_name = service
      username = neutron
      password = NEUTRON_PASS
      service_metadata_proxy = true
      metadata_proxy_shared_secret = METADATA_SECRET
  ```
  -Đồng bộ database Neutron:
  ```sh
    su -s /bin/sh -c "neutron-db-manage --config-file /etc/neutron/neutron.conf \
    --config-file /etc/neutron/plugins/ml2/ml2_conf.ini upgrade head" neutron
  ```
  ![](images/deloy_openstack/anh11.png)

  -Khởi động lại dịch vụ Neutron trên Controller Node:
  ```sh
    sudo systemctl restart neutron-server neutron-openvswitch-agent neutron-dhcp-agent neutron-metadata-agent
    sudo systemctl enable neutron-server neutron-openvswitch-agent neutron-dhcp-agent neutron-metadata-agent
  ```
  -Khởi động lại nova-api:
  ```sh
    sudo systemctl restart nova-api
  ```
### Cài đặt Cinder 
  -Trên Controller tạo database cho Cinder:
  ```sh
    mysql -u root -p
  ```
  ```sh
    MariaDB [(none)]> CREATE DATABASE cinder;
    MariaDB [(none)]> GRANT ALL PRIVILEGES ON cinder.* TO 'cinder'@'localhost' IDENTIFIED BY 'CINDER_DBPASS';
    MariaDB [(none)]> GRANT ALL PRIVILEGES ON cinder.* TO 'cinder'@'%' IDENTIFIED BY 'CINDER_DBPASS';
  ```
  -Vào lại môi trường admin:
  ```sh
    source admin-opensc.sh
  ```
  -Tạo và cấu hình user, service cho cinder:
  ```sh
    openstack user create --domain default --password-prompt cinder
    openstack role add --project service --user cinder admin
    openstack service create --name cinder --description "OpenStack Block Storage" block-storage
    openstack endpoint create --region RegionOne block-storage public http://controller:8776/v3
    openstack endpoint create --region RegionOne block-storage internal http://controller:8776/v3
    openstack endpoint create --region RegionOne block-storage admin http://controller:8776/v3
  ```
![](images/deloy_openstack/anh13.png)

  -Cài đặt các gói cần thiết:
  ```sh
     apt install cinder-api cinder-scheduler
  ```
### Cài đặt Horizon (Dashboard)
  -Trên Controller Node:
  ```sh
    sudo apt install openstack-dashboard -y
  ```
  -Sửa file cấu hình Horizon:
  ```sh
    sudo nano /etc/openstack-dashboard/local_settings.py
  ```
  -Cấu hình file `local_settings.py`:
  ```sh
      ALLOWED_HOSTS = ['*']
      OPENSTACK_HOST = "controller"
      OPENSTACK_KEYSTONE_URL = "http://%s:5000/v3" % OPENSTACK_HOST
      OPENSTACK_KEYSTONE_MULTIDOMAIN_SUPPORT = True
      SESSION_ENGINE = 'django.contrib.sessions.backends.cache'
      CACHES = {
          'default': {
              'BACKEND': 'django.core.cache.backends.memcached.MemcachedCache',
              'LOCATION': 'controller:11211',
                    }
                }
      OPENSTACK_API_VERSIONS = {
                "identity": 3,
                "image": 2,
                "volume": 3,
            }
      OPENSTACK_KEYSTONE_DEFAULT_DOMAIN = "Default"
      OPENSTACK_NEUTRON_NETWORK = {
    'enable_router': False,
    'enable_quotas': False,
    'enable_ipv6': False,
    'enable_distributed_router': False,
    'enable_ha_router': False,
    'enable_fip_topology_check': False,
    }
      TIME_ZONE = "Asia/Ho_Chi_Minh"
  ```
  -Cấu hình file `/etc/httpd/conf.d/openstack-dashboard.conf`:
  ```sh
      WSGIApplicationGroup %{GLOBAL}
  ```
  -Restart lại apache2
  - Đăng nhập với tài khoản admin và mật khẩu là pass của KEYSTONE (lấy bằng cách export admin-openrc.sh)

  ![](images/deloy_openstack/anh12.png)

