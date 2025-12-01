# NAT (Network Address Translation)

## 1. Khái niệm
NAT dịch địa chỉ IP/port giữa mạng nội bộ và mạng công cộng, thường dùng cho chia sẻ một public IP hoặc chuyển port.

## 2. Các loại NAT
- SNAT (Source NAT): thay đổi địa chỉ nguồn (thường dùng khi outbound).
- DNAT (Destination NAT): thay đổi đích (port forwarding).
- Masquerade: dạng SNAT linh hoạt cho kết nối động.

## 3. Ví dụ iptables
SNAT:
```bash
iptables -t nat -A POSTROUTING -s 192.168.1.0/24 -o eth0 -j SNAT --to-source <PUBLIC_IP>
```
DNAT (port forwarding):
```bash
iptables -t nat -A PREROUTING -p tcp --dport 2222 -j DNAT --to-destination 192.168.1.50:22
```

## 4. Lưu ý
- Kết hợp với forwarding và policy routing nếu cần.
- Kiểm tra ip_forward = 1 trong /proc/sys/net/ipv4/ip_forward