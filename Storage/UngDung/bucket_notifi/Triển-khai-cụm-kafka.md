# TÀI LIỆU TRIỂN KHAI CỤM APACHE KAFKA (KRAFT MODE)
## Chuẩn bị
| Node ID | Vai trò (Role)     | Địa chỉ IP    | Port (Data / Metadata) |
|---------|--------------------|---------------|------------------------|
| 1       | broker, controller | <IP_NODE_1>   | 9092 / 9093            |
| 2       | broker, controller | <IP_NODE_2>   | 9092 / 9093            |
| 3       | broker, controller | <IP_NODE_3>   | 9092 / 9093            |

## Cài đặt
### Chuẩn bị môi trường
1. Cài đặt môi trường Java để Kafka vận hành
```sh 
sudo apt update
sudo apt install -y openjdk-17-jdk
# Trên CentOS
dnf install -y java-17-openjdk-devel
```
2. Tải và giải nén Kafka
```sh
wget https://www.apache.org/dyn/closer.lua/kafka/4.2.0/kafka_2.13-4.2.0.tgz?action=download
tar -xzf kafka_2.13-4.2.0.tgz
sudo mv kafka_2.13-4.2.0 /opt/kafka
```
3. Cấu hình 
- Cấu hình tại `/opt/kafka/config/server.properties`. Chỉnh sửa và cấu hình các dòng sau ở cả 3 nodes
```sh
process.roles=broker,controller
node.id=1 #Chỉnh theo từng node
controller.quorum.voters=10.2.4.212:9093,10.2.4.217:9093,10.2.4.216:9093 #Nhớ là đúng thứ tự
listeners=PLAINTEXT://10.2.4.212:9092,CONTROLLER://10.2.4.212:9093 #Lắng nghe địa chỉ ip của máy host
inter.broker.listener.name=PLAINTEXT
advertised.listeners=PLAINTEXT://10.2.4.212:9092,CONTROLLER://10.2.4.212:9093
controller.listener.names=CONTROLLER
log.dirs=/var/lib/kafka
```
- Trên 1 node random mã uuid, lưu lại để format cho chung 3 nodes
```sh 
/opt/kafka/bin/kafka-storage.sh random-uuid
```
- Format trên cả 3 nodes chung uuid

  - Trên control node
```sh
/opt/kafka/bin/kafka-storage.sh format -t <Tên-uuid> -c /opt/kafka/config/server.properties --initial-controllers 1@192.168.1.193:9093:<tên-uuid>
```
  - Trên node khác
```sh
/opt/kafka/bin/kafka-storage.sh format -t CJ8Zgn66SaWSQ3EYOMbWKg -c /opt/kafka/config/server.properties --no-initial-controllers 
```

- Khởi động server Kafka
```sh
    /opt/kafka/bin/kafka-server-start.sh -daemon /opt/kafka/config/server.properties
```
- Check cụm đã hoạt động đúng chưa
```sh
/opt/kafka/bin/kafka-metadata-quorum.sh --bootstrap-server 10.2.4.209:9092 describe --status
```








