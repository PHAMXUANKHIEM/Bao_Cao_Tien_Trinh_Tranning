1. VLAN là gì? Ứng dụng VLAN
    VLAN (Virtual LAN): VLAN cho phép chia nhỏ một switch vật lý thành nhiều mạng logic khác nhau.

    Ung dụng của VLAN:

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
3. Routing giữa các VLAN
    Router-on-a-stick: Sử dụng một interface vật lý trên router để định tuyến giữa nhiều VLAN qua trunk link.

    Switch L3 hoặc Layer 3 Switch: Switch có khả năng định tuyến giữa các VLAN nội bộ mà không cần router bên ngoài.
4. Bonding với VLAN
    Bonding (Link Aggregation): Kết hợp nhiều interface vật lý thành một interface logic để tăng băng thông và dự phòng.

    Bonding + VLAN: Tạo trunk trên interface bonding để tận dụng băng thông tổng hợp và định tuyến giữa các VLAN.