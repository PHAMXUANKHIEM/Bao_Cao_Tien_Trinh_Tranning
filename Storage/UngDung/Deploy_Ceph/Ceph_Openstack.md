# Tích hợp Ceph vào Openstack
Bước 1: Tạo Ceph Pool
  ```sh
  ceph osd pool create volumes 128
  ceph osd pool create backups 128
  ceph osd pool create images 128
  ceph osd pool create vms 128
  ```
Bước 2: Cài đặt và cấu hình Ceph Clients
2.1 Cài đặt các thư viện 
 - Trên nodes cài `nova-compute`, `cinder-backup`, `cinder-volume` phải cài các thư viện python cần thiết:
 ```sh
 apt install python3-rbd
 apt install ceph-common
 ```
 - Trên node cài glance-api cài đặt thư viện python:
 ```sh
 apt install python3-rbd
 ```
2.2 Tạo và copy file `ceph.conf`
 - Trên các nodes chạy dịch vụ `nova-compute`, `cinder-backup`, `cinder-volume`, `glance-api` tạo thư mục `/etc/ceph`
 ```sh
 mkdir /etc/ceph
 ```
 - Trên máy Ceph copy cấu hình Ceph vào trong các nodes của Openstack. Các nodes chạy dịch vụ `nova-compute`, `cinder-backup`, `cinder-volume`, `glance-api` phải đc copy file này từ máy Ceph
 ```sh
 scp /etc/ceph/ceph.conf nodes:/etc/ceph
 ```
2.3 Cấu hình Ceph Client Authencation
 - Trên nodes chạy Ceph Monitor, tạo mới user cho Cinder, Cinder Backup và Glance
 ```sh
 ceph auth get-or-create client.cinder mon 'allow r' osd 'allow class-read object_prefix rbd_children, allow rwx pool=volumes, allow rwx pool=vms, allow rx pool=images'

 ceph auth get-or-create client.cinder-backup mon 'allow r' osd 'allow class-read object_prefix rbd_children, allow rwx pool=backups'

 ceph auth get-or-create client.glance mon 'allow r' osd 'allow class-read object_prefix rbd_children, allow rwx pool=images'
```
 - Tạo và copy chúng đúng vào các nodes đang cài đặt dịch vụ trùng khớp
 ```sh
 ceph auth get-or-create client.cinder | ssh lab-hapu-ctl sudo tee /etc/ceph/ceph.client.cinder.keyring
ssh lab-hapu-ctl chown cinder:cinder /etc/ceph/ceph.client.cinder.keyring

ceph auth get-or-create client.cinder-backup | ssh lab-hapu-ctl tee /etc/ceph/ceph.client.cinder-backup.keyring
ssh lab-hapu-ctl chown cinder:cinder /etc/ceph/ceph.client.cinder-backup.keyring

ceph auth get-or-create client.glance | ssh lab-hapu-ctl sudo tee /etc/ceph/ceph.client.glance.keyring
ssh lab-hapu-ctl chown glance:glance /etc/ceph/ceph.client.glance.keyring
```
![](imgaes/anh21.png)

Bước 3: Cấu hình Openstack sử dụng Ceph
 1. Cấu hình Cinder
  - Vào `/etc/cinder/cinder.conf` cấu hình `[Default]`
  ```sh
      enabled_backends = ceph
      glance_api_version = 2
  ```
   Tạo `[ceph]` trong `cinder.conf`:
   ```sh
   [ceph]
   volume_driver = cinder.volume.drivers.rbd.RBDDriver 
   rbd_cluster_name = ceph 
   rbd_pool = volumes
   rbd_user = cinder
   rbd_ceph_conf = /etc/ceph/ceph.conf
   rbd_flatten_volume_from_snapshot = false
   rbd_secret_uuid = 4b5fd580-360c-4f8c-abb5-c83bb9a3f964
   rbd_max_clone_depth = 5
   rbd_store_chunk_size = 4
   rados_connect_timeout = -1 
   ```
 2. Cấu hình cinder-backup
  - Vào `[ceph]` cấu hình:
  ```sh
    [ceph]
    volume_driver = cinder.volume.drivers.rbd.RBDDriver
    rbd_cluster_name = ceph
    rbd_pool = volumes
    rbd_user = cinder
    rbd_ceph_conf = /etc/ceph/ceph.conf
    rbd_flatten_volume_from_snapshot = false
    rbd_secret_uuid = 4b5fd580-360c-4f8c-abb5-c83bb9a3f964
    rbd_max_clone_depth = 5
    rbd_store_chunk_size = 4
    rados_connect_timeout = -1

    backup_driver = cinder.backup.drivers.ceph
    backup_ceph_user = cinder-backup
    backup_ceph_conf = /etc/ceph/ceph.conf
    backup_ceph_chunk_size = 134217728
    backup_ceph_pool = backups
    backup_ceph_stripe_unit = 0
    backup_ceph_stripe_count = 0
    restore_discard_excess_bytes = true
```
  -Cấu hình trong horizon :
```sh 
OPENSTACK_CINDER_FEATURES = {
  'enable_backup': True,
}
 ```
 3. Cấu hình Glance
  - Vào `/etc/glance/glance-api.conf`: 
  ```sh
  [Default]
  show_image_direct_url = True
  [glance_store]
  stores = rbd
  default_store = rbd
  rbd_store_chunk_size = 8
  rbd_store_pool = images
  rbd_store_user = glance
  rbd_store_ceph_conf = /etc/ceph/ceph.conf
  ```
 4. Cấu hình nova
  - Trên nodes Ceph cấu hình `[client]` vào `/etc/ceph/ceph.conf`:
  ```sh
  [client]
rbd cache = true
rbd cache writethrough until flush = true
rbd concurrent management ops = 20
admin socket = /var/run/ceph/guests/$cluster-$type.$id.$pid.$cctid.asok
log file = /var/log/ceph/qemu-guest-$pid.log
```
  - Tạo thư mục cho admin socket và log file 
  ```sh
  mkdir -p /var/run/ceph/guests/ /var/log/ceph/
  ```
 - Vào lại node cài nova-compute, cấu hình `/etc/nova/nova.conf`
 ```sh
 [libvirt]
images_type = rbd
images_rbd_pool = vms
images_rbd_ceph_conf = /etc/ceph/ceph.conf
rbd_user = cinder
rbd_secret_uuid = 4b5fd580-360c-4f8c-abb5-c83bb9a3f964
disk_cachemodes="network=writeback"
inject_password = false
inject_key = false
inject_partition = -2
live_migration_flag="VIR_MIGRATE_UNDEFINE_SOURCE,VIR_MIGRATE_PEER2PEER,VIR_MIGRATE_LIVE,VIR_MIGRATE_PERSIST_DEST,VIR_MIGRATE_TUNNELLED"
hw_disk_discard = unmap
```
5. Restart lại dịch vụ
```sh
systemctl restart openstack-cinder-volume
systemctl restart openstack-cinder-backup
systemctl restart openstack-glance-api
systemctl restart openstack-nova-compute
```
6. Test tạo 1 images trên openstack

![](imgaes/anh22.png)
