# Cài Monitor cho Cephadm 
Bước 1: Kiểm tra và bật module của prometheus, grafana và dashboard
```sh
cephadm shell ceph mgr enable module prometheus
cephadm shell ceph mgr enable module grafana
cephadm shell ceph mgr enable module dashboard
```
Bước 2: Tạo file grafana.yml
```sh
service_type: grafana
spec:
  initial_admin_password: admin
```
Bước 3: Apply
```sh
ceph orch apply -i grafana.yml
```

Bước 4: Reset
```sh
ceph dashboard reset-grafana-api-password
```

Bước 5: Đăng nhập giao diện Grafana

![](imgaes/anh22.png)