1. VLAN là gì? Ứng dụng VLAN
VLAN (Virtual LAN) = Mạng LAN ảo

VLAN cho phép chia nhỏ một switch vật lý thành nhiều mạng logic khác nhau.

  Lợi ích

Tách biệt mạng → giảm broadcast → tối ưu hiệu năng.

Tăng bảo mật → VLAN Guest, VLAN Server, VLAN Employee tách biệt.

Dễ quản lý → nhóm phòng ban theo VLAN.

Triển khai mạng lớn → các switch vẫn giữ được phân vùng logic.
2. Trunking là gì?
Trunk = Đường truyền mang nhiều VLAN qua một dây uplink.

Access port → mang 1 VLAN

Trunk port → mang nhiều VLAN (tag bằng 802.1Q)
Trunk thường dùng để:

Kết nối switch → switch

Kết nối switch → router (Router-on-a-stick)

Kết nối switch → ESXi/vCenter (VST/EST)