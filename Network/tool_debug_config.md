# Tool debug,  config network
### 1. ip link
- Là một lệnh trong bộ iproute2 dung để quản lý các interface trong network trên Linux  
- Một số lệnh của ip link"
  - `ip link` hoặc `ip link show`: Xem các interface trên máy
  - `ip link set + tên_interface + up/down`: bật tắt interface  
  - `ip link set + tên_interface_cũ + tên_interface cũ`: Đổi name của interface
  - `ip link show + interface`: Xem MAC, MTU
  - 