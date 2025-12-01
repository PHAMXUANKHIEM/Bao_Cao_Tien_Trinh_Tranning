# IPTABLES 
## 1. Bảng (tables) chính và chuỗi (chains)

- Bảng phổ biến:
  - `filter` — mặc định, dùng để chặn/cho phép (ACCEPT, DROP, REJECT).
  - `nat` — xử lý NAT (PREROUTING, POSTROUTING, OUTPUT).
  - `mangle` — thay đổi các trường header (TOS, TTL, MARK).
  - `raw` — thao tác trước connection tracking.
  - `security` — dùng nếu có SELinux/LSM.

- Chuỗi mặc định (ví dụ trong `filter`):
  - `INPUT` — gói đến máy local.
  - `OUTPUT` — gói xuất phát từ máy local.
  - `FORWARD` — gói đi qua máy (khi làm router).

Luồng xử lý gói (tóm tắt): `raw` → `mangle` PREROUTING → `nat` PREROUTING → routing → `filter` (FORWARD/INPUT/OUTPUT) → `nat` POSTROUTING → `mangle` POSTROUTING.
## 2. Target (hành động) thông dụng

- `ACCEPT`: cho phép gói tiếp tục.
- `DROP`: loại bỏ gói, không phản hồi.
- `REJECT`: từ chối và gửi trả lỗi (ví dụ ICMP).
- `LOG`: ghi log (không thay đổi hành vi tiếp theo).
- `DNAT`, `SNAT`, `MASQUERADE`: thay đổi địa chỉ IP (NAT).
- `REDIRECT`: chuyển hướng tới localhost (transparent proxy).
- `MARK`: gắn nhãn để dùng cho routing/QoS.

Ví dụ:

```sh
iptables -A INPUT -p tcp --dport 22 -j ACCEPT
iptables -t nat -A POSTROUTING -s 192.168.1.0/24 -o eth0 -j MASQUERADE
iptables -A FORWARD -m conntrack --ctstate ESTABLISHED,RELATED -j ACCEPT
```
## 3. Các điều kiện (matches) hay dùng

- `-p <protocol>`: `tcp`, `udp`, `icmp`.
- `-s <ip>` / `-d <ip>`: IP nguồn / đích (hỗ trợ CIDR).
- `-i <iface>` / `-o <iface>`: interface vào / ra.
- `--sport` / `--dport`: cổng nguồn / đích (với TCP/UDP).
- `-m conntrack --ctstate <state>`: `NEW`, `ESTABLISHED`, `RELATED`, `INVALID`.
- `-m multiport --dports 80,443,22`: match nhiều port.
- `-m limit --limit 5/min`: giới hạn tần suất (thường dùng với LOG).

Chú ý: `-m state` cũ được thay bằng `-m conntrack` trên hệ thống hiện đại.

## 4. Lệnh quản lý cơ bản

- Thêm rule vào cuối chuỗi:
```sh
iptables -A <CHAIN> <match> -j <TARGET>
```
- Chèn rule vào đầu chuỗi (hoặc vị trí số):
```sh
iptables -I <CHAIN> [num] <match> -j <TARGET>
```
- Xóa rule theo số hoặc theo spec:
```sh
iptables -D <CHAIN> <num>
iptables -D <CHAIN> <rule-spec>
```
- Liệt kê rule:
```sh
iptables -L -n -v --line-numbers
iptables -S   # hiển thị dưới dạng command
```
- Flush (xóa tất cả rule trong table/chain):
```sh
iptables -F            # flush filter (mặc định)
iptables -t nat -F     # flush table nat
```

## 5. Lưu/khôi phục cấu hình

- Lưu: `iptables-save > /path/to/file`
- Khôi phục: `iptables-restore < /path/to/file`
- Trên Debian/Ubuntu: dùng `iptables-persistent` để auto-load rules trên boot.
- Trên RHEL/CentOS: cấu hình có thể nằm ở `/etc/sysconfig/iptables`.

Đảm bảo bật IP forwarding nếu cần NAT/router:

```sh
sudo sysctl -w net.ipv4.ip_forward=1
# hoặc chỉnh /etc/sysctl.conf
# net.ipv4.ip_forward = 1
```

## 6. NAT (SNAT / DNAT / MASQUERADE)

- SNAT: thay địa chỉ nguồn cố định (thường dùng cho IP tĩnh):
```sh
iptables -t nat -A POSTROUTING -s 10.10.0.0/24 -o eth0 -j SNAT --to-source 203.0.113.5
```
- MASQUERADE: dùng khi IP outbound động (ví dụ PPPoE, DHCP):
```sh
iptables -t nat -A POSTROUTING -s 10.10.0.0/24 -o eth0 -j MASQUERADE
```
- DNAT / port forwarding:
```sh
iptables -t nat -A PREROUTING -i eth0 -p tcp --dport 80 -j DNAT --to-destination 10.10.0.2:80
```

## 7. Ví dụ cấu hình cơ bản

1) Cho phép SSH & HTTP, chặn các kết nối mới khác vào máy:

```sh
iptables -P INPUT DROP
iptables -P FORWARD DROP
iptables -P OUTPUT ACCEPT

# allow loopback
iptables -A INPUT -i lo -j ACCEPT

# established
iptables -A INPUT -m conntrack --ctstate ESTABLISHED,RELATED -j ACCEPT

# allow SSH, HTTP
iptables -A INPUT -p tcp --dport 22 -j ACCEPT
iptables -A INPUT -p tcp --dport 80 -j ACCEPT

# allow ping
iptables -A INPUT -p icmp --icmp-type echo-request -j ACCEPT
```

2) NAT mạng nội bộ ra Internet (router):

```sh
sudo sysctl -w net.ipv4.ip_forward=1
iptables -t nat -A POSTROUTING -s 10.10.0.0/24 -o eth0 -j MASQUERADE
iptables -A FORWARD -i eth0 -o br-lan -m conntrack --ctstate RELATED,ESTABLISHED -j ACCEPT
iptables -A FORWARD -i br-lan -o eth0 -j ACCEPT
```

3) Ghi log trước khi drop (cẩn thận: LOG có thể tạo nhiều log):

```sh
iptables -A INPUT -m limit --limit 5/min -j LOG --log-prefix "IPTables-Dropped: " --log-level 4
iptables -A INPUT -j DROP
```
## 8. Module kernel & cấu hình hệ thống

- Một số module/xtables extension cần thiết có thể bao gồm: `nf_conntrack`, `iptable_nat`, `xt_conntrack`, `xt_multiport`, v.v. Hiện các kernel mới dùng `nf-*` và `xt_*`.
- Kiểm tra các module đã load bằng `lsmod | grep conntrack`.

---

## 9. Ưu điểm, hạn chế và công cụ cao cấp

- Ưu điểm: tích hợp trong kernel, hiệu năng cao, rất linh hoạt.
- Hạn chế: cú pháp rườm rà, khó quản lý rule lớn.
- Frontends phổ biến: `ufw` (Ubuntu), `firewalld` (Fedora/CentOS) — hữu ích để đơn giản hoá quản lý.
