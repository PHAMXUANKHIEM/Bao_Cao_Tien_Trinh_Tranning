Nova
1.Khai niệm OpenStack Nova
- OpenStack Nova là thành phần quản lý tính toán (Compute) trong nền tảng điện toán đám mây OpenStack.
- Nova chịu trách nhiệm cung cấp và quản lý các máy ảo (VMs) và các tài nguyên tính toán khác trong môi trường đám mây.
- Mục đích chính của Nova bao gồm:
  - Cung cấp khả năng triển khai, quản lý và mở rộng các máy ảo một cách linh hoạt.
  - Hỗ trợ nhiều loại hypervisor khác nhau như KVM, Xen, VMware, v.v.
  - Tích hợp với các dịch vụ khác trong OpenStack như Neutron (network), Cinder (storage), và Glance (images).
- Nova thường được sử dụng trong các môi trường đám mây công cộng và riêng tư để cung cấp tài nguyên tính toán theo yêu cầu.
- Nova bao gồm các thành phần chính như:
  - Nova Compute: Quản lý vòng đời của các máy ảo.
  - Nova Scheduler: Quyết định nơi triển khai các máy ảo dựa trên tài nguyên có sẵn.
  - Nova API: Cung cấp giao diện lập trình ứng dụng để tương tác với dịch vụ Nova.
  - Nova Conductor: Hỗ trợ giao tiếp giữa các thành phần khác nhau của Nova.
2. Cách hoạt động của OpenStack Nova
- Khi người dùng gửi yêu cầu tạo máy ảo thông qua giao diện API của Nova, Nova sẽ thực hiện các bước sau:
  1. Xác thực và ủy quyền yêu cầu từ người dùng.
  2. Nova Scheduler sẽ kiểm tra tài nguyên có sẵn và quyết định nơi triển khai máy ảo.
  3. Nova Compute sẽ tạo và cấu hình máy ảo trên hypervisor được chọn.
  4. Nova sẽ theo dõi trạng thái của máy ảo và cung cấp các chức năng quản lý như khởi động, tắt, và xóa máy ảo.
- Nova cũng tích hợp với các dịch vụ khác trong OpenStack để cung cấp các tính năng bổ sung như mạng ảo, lưu trữ, và hình ảnh máy ảo.
3. Nova Compute
- Nova Compute là thành phần chịu trách nhiệm quản lý vòng đời của các máy ảo trong OpenStack.
- Nó tương tác trực tiếp với hypervisor để tạo, khởi động, tắt, và xóa các máy ảo.
- Nova Compute cũng theo dõi trạng thái của các máy ảo và báo cáo thông tin này cho các thành phần khác của Nova.
- Nova Compute hỗ trợ nhiều loại hypervisor khác nhau, cho phép người dùng lựa chọn nền tảng phù hợp với nhu cầu của họ.
- Ngoài ra, Nova Compute còn cung cấp các tính năng như:
  - Quản lý tài nguyên tính toán như CPU, RAM, và lưu trữ.
  - Hỗ trợ các tính năng nâng cao như live migration, snapshot, và resizing của máy ảo.
  - Tích hợp với các dịch vụ mạng và lưu trữ để cung cấp môi trường hoàn chỉnh cho các máy ảo.  
  - Nova Compute thường được triển khai trên các máy chủ vật lý trong cụm OpenStack để cung cấp tài nguyên tính toán cho người dùng.
4. Nova Scheduler
- Nova Scheduler là thành phần chịu trách nhiệm quyết định nơi triển khai các máy ảo trong OpenStack.
- Nó sử dụng các thuật toán và chính sách để lựa chọn máy chủ vật lý phù hợp dựa trên tài nguyên có sẵn và yêu cầu của máy ảo.
- Tài nguyên hiện có trên các máy chủ vật lý được theo dõi và cập nhật liên tục để đảm bảo quyết định của Nova Scheduler là chính xác.
- Nova Scheduler hỗ trợ nhiều thuật toán lập lịch khác nhau, bao gồm:
  - Least Loaded: Chọn máy chủ có tài nguyên sử dụng thấp nhất.
  - Random: Chọn máy chủ ngẫu nhiên từ danh sách các máy chủ có sẵn.
  - Custom Filters: Cho phép người dùng định nghĩa các bộ lọc tùy chỉnh để kiểm soát quá trình lập lịch.
- Nova Scheduler cũng có thể được cấu hình để hỗ trợ các chính sách nâng cao như cân bằng tải, ưu tiên tài nguyên, và hạn chế tài nguyên.
- Khi một yêu cầu tạo máy ảo được gửi đến Nova, Nova Scheduler sẽ phân tích yêu cầu và tài nguyên hiện có để đưa ra quyết định về việc triển khai máy ảo trên máy chủ vật lý phù hợp nhất.
5. Nova API
- Nova API là giao diện lập trình ứng dụng (API) chính của OpenStack Nova, cho phép người dùng và các dịch vụ khác tương tác với dịch vụ Nova.
- Nova API cung cấp các điểm cuối (endpoints) để thực hiện các thao tác như tạo, quản lý, và xóa máy ảo, cũng như truy xuất thông tin về tài nguyên tính toán.
- Nova API hỗ trợ các phương thức HTTP như GET, POST, PUT, và DELETE để thực hiện các thao tác khác nhau trên tài nguyên Nova.
- Nova API tuân thủ các tiêu chuẩn RESTful, giúp dễ dàng tích hợp với các ứng dụng và dịch vụ khác trong hệ sinh thái OpenStack.
- Ngoài ra, Nova API còn hỗ trợ các tính năng như:
  - Xác thực và ủy quyền người dùng thông qua Keystone.
  - Hỗ trợ phiên bản API để đảm bảo tương thích ngược khi có các thay đổi trong API.
  - Cung cấp các tham số tùy chọn để kiểm soát hành vi của các thao tác trên máy ảo.
- Nova API thường được sử dụng bởi các công cụ dòng lệnh OpenStack CLI, giao diện người dùng Horizon, và các ứng dụng bên thứ ba để quản lý tài nguyên tính toán trong OpenStack.
6. Nova Conductor
- Nova Conductor là thành phần trung gian trong OpenStack Nova, chịu trách nhiệm hỗ trợ giao tiếp giữa các thành phần khác nhau của Nova.
- Nó giúp giảm tải công việc từ Nova Compute bằng cách xử lý các tác vụ liên quan đến cơ sở dữ liệu và các dịch vụ khác.
- Nova Conductor thực hiện các nhiệm vụ như:
  - Quản lý trạng thái của các máy ảo và tài nguyên tính toán trong cơ sở dữ liệu.
  - Hỗ trợ giao tiếp giữa Nova Compute và các dịch vụ khác như Glance (hình ảnh máy ảo) và Neutron (mạng).
  - X ử lý các yêu cầu liên quan đến việc tạo, cập nhật, và xóa máy ảo.
- Nova Conductor giúp cải thiện hiệu suất và độ tin cậy của hệ thống bằng cách tách biệt các nhiệm vụ quản lý cơ sở dữ liệu khỏi các tác vụ tính toán.
- Nó cũng giúp đảm bảo tính nhất quán của dữ liệu trong môi trường phân tán của OpenStack.
- Nova Conductor thường được triển khai dưới dạng một dịch vụ riêng biệt trong cụm OpenStack, hoạt động song song với các thành phần khác của Nova để cung cấp trải nghiệm quản lý tài nguyên tính toán hiệu quả và ổn định. 
7. Cách triển khai OpenStack Nova
- Để triển khai OpenStack Nova, cần thực hiện các bước cơ bản sau:
  1. Cài đặt và cấu hình các thành phần cơ bản của OpenStack như Keystone (authentication), Glance (images), và Neutron (network).
  2. Cài đặt và cấu hình Nova Controller, bao gồm Nova API, Nova Scheduler, và Nova Conductor.
  3. Cài đặt và cấu hình Nova Compute trên các máy chủ vật lý để cung cấp tài nguyên tính toán.
  4. Cấu hình các tham số cần thiết trong file cấu hình Nova (`nova.conf`), bao gồm thông tin về cơ sở dữ liệu, dịch vụ mạng, và các tùy chọn hypervisor.
  5. Khởi động các dịch vụ Nova và kiểm tra trạng thái hoạt động của chúng.
  6. Tạo và quản lý các máy ảo thông qua giao diện API hoặc giao diện người dùng Horizon.
- Quá trình triển khai Nova có thể được thực hiện thủ công hoặc sử dụng các công cụ tự động hóa như DevStack, OpenStack-Ansible, hoặc Kolla-Ansible để đơn giản hóa việc cài đặt và cấu hình.
- Sau khi triển khai, cần theo dõi và quản lý các dịch vụ Nova để đảm bảo hiệu suất và độ tin cậy của hệ thống tính toán trong môi trường OpenStack.
