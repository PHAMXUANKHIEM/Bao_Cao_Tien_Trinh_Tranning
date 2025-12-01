# Bandwidth Limiting

## 1. Khái niệm
Giới hạn băng thông (bandwidth limiting) là việc kiểm soát lưu lượng mạng để đảm bảo chất lượng dịch vụ, tránh quá tải và phân bổ công bằng cho các ứng dụng.

## 2. Các phương pháp chính
- Traffic shaping (ví dụ: tc với qdisc/classful qdiscs).
- Policing (giới hạn và bỏ gói vượt).
- Rate limiting trên firewall (iptables + hashlimit/module tương tự).
- QoS trên thiết bị mạng (DSCP, queuing).

## 3. Công cụ phổ biến (Linux)
- tc (traffic control) — netem, htb, tbf.
- iptables/xtables với các module như limit, hashlimit.
- Wondershaper (dùng nhanh để giới hạn uplink/downlink).

## 4. Ví dụ cơ bản (tc + htb)
```bash
# Tạo root qdisc
tc qdisc add dev eth0 root handle 1: htb default 30

# Tạo class cho tổng băng thông 10mbit
tc class add dev eth0 parent 1: classid 1:1 htb rate 10mbit

# Tạo class con (5mbit)
tc class add dev eth0 parent 1:1 classid 1:10 htb rate 5mbit ceil 5mbit
tc qdisc add dev eth0 parent 1:10 handle 10: sfq
```

## 5. Lời khuyên
- Test trên môi trường staging trước khi áp dụng production.
- Kết hợp đo lường (vnstat, iftop, tc -s qdisc) để tinh chỉnh.