# RBD - Quản lý RADOS Block Device (RBD) Images

## Giới thiệu

`rbd` là một tiện ích để thao tác với các RBD images, được sử dụng bởi Linux rbd driver và rbd storage driver cho QEMU/KVM. RBD images là các block devices đơn giản được stripe qua các objects và lưu trữ trong RADOS object store. Kích thước của objects mà image được stripe phải là lũy thừa của 2.

## Cú pháp

```
rbd [ -c ceph.conf ] [ -m monaddr ] [–cluster cluster-name] [ -p | –pool pool ] [ command … ]
```

## Mô tả

rbd là một công cụ để quản lý RADOS Block Device (RBD) images.

## Tùy chọn

- `-c ceph.conf, --conf ceph.conf`: Sử dụng file cấu hình ceph.conf thay vì mặc định /etc/ceph/ceph.conf để xác định địa chỉ monitor khi khởi động.
- `-m monaddress[:port]`: Kết nối với monitor được chỉ định (thay vì tìm qua ceph.conf).
- `--cluster cluster-name`: Sử dụng tên cluster khác với tên cluster mặc định ceph.
- `-p pool-name, --pool pool-name`: Tương tác với pool được chỉ định. Bắt buộc cho hầu hết các lệnh.
- `--namespace namespace-name`: Sử dụng namespace image được định nghĩa trước trong pool.
- `--no-progress`: Không xuất thông tin tiến trình (đi đến standard error theo mặc định cho một số lệnh).

## Tham số

- `--image-format format-id`: Chỉ định layout object nào sẽ được sử dụng. Mặc định là 2.
  - format 1: (deprecated) Sử dụng format gốc cho RBD image mới. Format này được hiểu bởi tất cả các phiên bản librbd và kernel rbd module, nhưng không hỗ trợ các tính năng mới hơn như cloning.
  - format 2: Sử dụng RBD format thứ hai, được hỗ trợ bởi librbd từ bản Bobtail và kernel rbd module từ kernel 3.10 (trừ "fancy" striping, được hỗ trợ từ kernel 4.17). Thêm hỗ trợ cho cloning và dễ dàng mở rộng để cho phép nhiều tính năng hơn trong tương lai.
- `-s size-in-M/G/T, --size size-in-M/G/T`: Chỉ định kích thước của RBD image mới hoặc kích thước mới của RBD image hiện có trong M/G/T. Nếu không có hậu tố, đơn vị M được giả định.
- `--object-size size-in-B/K/M`: Chỉ định kích thước object trong B/K/M. Kích thước object sẽ được làm tròn lên lũy thừa gần nhất của 2; nếu không có hậu tố, đơn vị B được giả định. Kích thước object mặc định là 4M, nhỏ nhất là 4K và tối đa là 32M.
- `--stripe-unit size-in-B/K/M`: Chỉ định kích thước stripe unit trong B/K/M. Nếu không có hậu tố, đơn vị B được giả định. Xem phần striping để biết thêm chi tiết.
- `--stripe-count num`: Chỉ định số lượng objects để stripe trước khi lặp lại object đầu tiên. Xem phần striping để biết thêm chi tiết.
- `--snap snap`: Chỉ định tên snapshot cho thao tác cụ thể.
- `--id username`: Chỉ định tên người dùng (không có tiền tố `client.`) để sử dụng với lệnh map.
- `--keyring filename`: Chỉ định file keyring chứa secret cho user được chỉ định để sử dụng với lệnh map. Nếu không chỉ định, các vị trí keyring mặc định sẽ được tìm kiếm.
- `--keyfile filename`: Chỉ định file chứa secret key của `--id` `user` để sử dụng với lệnh map. Tùy chọn này bị ghi đè bởi `--keyring` nếu cả hai đều được chỉ định.
- `--shared lock-tag`: Tùy chọn cho lock add cho phép nhiều client khóa cùng một image nếu họ sử dụng cùng tag. Tag là một chuỗi tùy ý. Điều này hữu ích cho các tình huống mà image phải được mở từ nhiều client cùng lúc, như trong live migration của máy ảo, hoặc để sử dụng dưới clustered file system.
- `--format format`: Chỉ định định dạng xuất (mặc định: plain, json, xml).
- `--pretty-format`: Làm cho json hoặc xml formatted output dễ đọc hơn cho con người.
- `-o krbd-options, --options krbd-options`: Chỉ định tùy chọn nào để sử dụng khi map hoặc unmap image qua rbd kernel driver. krbd-options là danh sách tùy chọn được phân tách bằng dấu phẩy (tương tự mount(8) mount options). Xem phần kernel rbd (krbd) options để biết thêm chi tiết.
- `--read-only`: Map image read-only. Tương đương với -o ro.
- `--image-feature feature-name`: Chỉ định tính năng RBD format 2 nào nên được bật khi tạo image. Có thể bật nhiều tính năng bằng cách lặp lại tùy chọn này nhiều lần. Các tính năng được hỗ trợ:
  - layering: hỗ trợ layering
  - striping: hỗ trợ striping v2
  - exclusive-lock: hỗ trợ exclusive locking
  - object-map: hỗ trợ object map (yêu cầu exclusive-lock)
  - fast-diff: tính toán fast diff (yêu cầu object-map)
  - deep-flatten: hỗ trợ snapshot flatten
  - journaling: hỗ trợ journaled IO (yêu cầu exclusive-lock)
  - data-pool: hỗ trợ erasure coded pool
- `--image-shared`: Chỉ định rằng image sẽ được sử dụng đồng thời bởi nhiều client. Điều này sẽ tắt các tính năng phụ thuộc vào quyền sở hữu độc quyền của image.
- `--whole-object`: Chỉ định rằng diff nên được giới hạn ở các extents của một object đầy đủ thay vì hiển thị intra-object deltas. Khi tính năng object map được bật trên image, giới hạn diff ở object extents sẽ cải thiện đáng kể hiệu suất vì sự khác biệt có thể được tính toán bằng cách kiểm tra object map trong bộ nhớ thay vì truy vấn RADOS cho mỗi object trong image.
- `--limit`: Chỉ định giới hạn số lượng snapshots được phép.

## Lệnh

### bench
```
bench –io-type <read | write | readwrite | rw> [–io-size size-in-B/K/M/G/T] [–io-threads num-ios-in-flight] [–io-total size-in-B/K/M/G/T] [–io-pattern seq | rand] [–rw-mix-read read proportion in readwrite] image-spec
```
Tạo một loạt IOs đến image và đo throughput và latency IO. Nếu không có hậu tố, đơn vị B được giả định cho cả –io-size và –io-total. Mặc định: –io-size 4096, –io-threads 16, –io-total 1G, –io-pattern seq, –rw-mix-read 50.

### children
```
children snap-spec
```
Liệt kê các clones của image tại snapshot được chỉ định. Điều này kiểm tra mọi pool, và xuất ra poolname/imagename kết quả.

Yêu cầu image format 2.

### clone
```
clone [–object-size size-in-B/K/M] [–stripe-unit size-in-B/K/M –stripe-count num] [–image-feature feature-name] [–image-shared] parent-snap-spec child-image-spec
```
Tạo một clone (copy-on-write child) của parent snapshot. Kích thước object giống với parent image trừ khi được chỉ định. Kích thước giống với parent snapshot. Các tùy chọn –stripe-unit và –stripe-count là tùy chọn, nhưng phải được sử dụng cùng nhau.

Parent snapshot phải được bảo vệ (xem rbd snap protect). Yêu cầu image format 2.

### config
- `config global get config-entity key`: Lấy override cấu hình global-level.
- `config global list [–format plain | json | xml] [–pretty-format] config-entity`: Liệt kê overrides cấu hình global-level.
- `config global set config-entity key value`: Đặt override cấu hình global-level.
- `config global remove config-entity key`: Xóa override cấu hình global-level.
- `config image get image-spec key`: Lấy override cấu hình image-level.
- `config image list [–format plain | json | xml] [–pretty-format] image-spec`: Liệt kê overrides cấu hình image-level.
- `config image set image-spec key value`: Đặt override cấu hình image-level.
- `config image remove image-spec key`: Xóa override cấu hình image-level.
- `config pool get pool-name key`: Lấy override cấu hình pool-level.
- `config pool list [–format plain | json | xml] [–pretty-format] pool-name`: Liệt kê overrides cấu hình pool-level.
- `config pool set pool-name key value`: Đặt override cấu hình pool-level.
- `config pool remove pool-name key`: Xóa override cấu hình pool-level.

### cp
```
cp (src-image-spec | src-snap-spec) dest-image-spec
```
Sao chép nội dung của src-image vào dest-image mới được tạo. dest-image sẽ có cùng kích thước, object size, và image format như src-image.

### create
```
create (-s | –size size-in-M/G/T) [–image-format format-id] [–object-size size-in-B/K/M] [–stripe-unit size-in-B/K/M –stripe-count num] [–thick-provision] [–no-progress] [–image-feature feature-name]… [–image-shared] image-spec
```
Tạo một RBD image mới. Bạn cũng phải chỉ định kích thước qua –size. Các tùy chọn –stripe-unit và –stripe-count là tùy chọn, nhưng phải được sử dụng cùng nhau. Nếu –thick-provision được bật, nó sẽ phân bổ đầy đủ storage cho image tại thời điểm tạo. Nó sẽ mất một thời gian dài để làm. Lưu ý: thick provisioning yêu cầu zeroing nội dung của toàn bộ image.

### deep cp
```
deep cp (src-image-spec | src-snap-spec) dest-image-spec
```
Deep copy nội dung của src-image vào dest-image mới được tạo. dest-image sẽ có cùng kích thước, object size, image format, và snapshots như src-image.

### device
- `device list [-t | –device-type device-type] [–format plain | json | xml] –pretty-format`: Hiển thị RBD images được map qua rbd kernel module (mặc định) hoặc device được hỗ trợ khác.
- `device map [-t | –device-type device-type] [–cookie device-cookie] [–show-cookie] [–read-only] [–exclusive] [-o | –options device-options] image-spec | snap-spec`: Map image được chỉ định thành block device qua rbd kernel module (mặc định) hoặc device được hỗ trợ khác (nbd trên Linux hoặc ggate trên FreeBSD).
- `device unmap [-t | –device-type device-type] [-o | –options device-options] image-spec | snap-spec | device-path`: Unmap block device đã được map qua rbd kernel module (mặc định) hoặc device được hỗ trợ khác.
- `device attach [-t | –device-type device-type] –device device-path [–cookie device-cookie] [–show-cookie] [–read-only] [–exclusive] [–force] [-o | –options device-options] image-spec | snap-spec`: Attach image được chỉ định vào block device được chỉ định (hiện tại chỉ nbd trên Linux). Thao tác này không an toàn và không nên được sử dụng bình thường. Đặc biệt, việc chỉ định image hoặc block device sai có thể dẫn đến mất dữ liệu vì không có validation nào được thực hiện bởi nbd kernel driver.
- `device detach [-t | –device-type device-type] [-o | –options device-options] image-spec | snap-spec | device-path`: Detach block device đã được map hoặc attach (hiện tại chỉ nbd trên Linux). Thao tác này không an toàn và không nên được sử dụng bình thường.

### diff
```
diff [–from-snap snap-name] [–whole-object] image-spec | snap-spec
```
Dump danh sách byte extents trong image đã thay đổi kể từ start snapshot được chỉ định, hoặc kể từ khi image được tạo. Mỗi dòng xuất bao gồm offset bắt đầu (trong bytes), độ dài của vùng (trong bytes), và 'zero' hoặc 'data' để chỉ ra vùng có thể chứa dữ liệu khác hay không.

### du
```
du [-p | –pool pool-name] [image-spec | snap-spec] [–merge-snapshots]
```
Sẽ tính toán disk usage được provisioned và thực tế của tất cả images và snapshots liên quan trong pool được chỉ định. Nó cũng có thể được sử dụng đối với individual images và snapshots.

Nếu RBD fast-diff feature không được bật trên images, thao tác này sẽ yêu cầu truy vấn OSDs cho mỗi potential object trong image.

–merge-snapshots sẽ merge snapshots used space vào parent images của chúng.

### encryption format
```
encryption format image-spec format passphrase-file [–cipher-alg alg]
```
Format image thành encrypted format. Tất cả dữ liệu trước đó được viết vào image sẽ trở nên không thể đọc được. Image đã được clone không thể được format, mặc dù encrypted images có thể được clone. Các format được hỗ trợ: luks1, luks2. Các cipher algorithms được hỗ trợ: aes-128, aes-256 (mặc định).

### export
```
export [–export-format format (1 or 2)] (image-spec | snap-spec) [dest-path]
```
Export image to dest path (sử dụng - cho stdout). –export-format chấp nhận '1' hoặc '2' hiện tại. Format 2 cho phép export không chỉ nội dung của image, mà còn snapshots và các properties khác, như image_order, features.

### export-diff
```
export-diff [–from-snap snap-name] [–whole-object] (image-spec | snap-spec) dest-path
```
Export incremental diff cho image to dest path (sử dụng - cho stdout). Nếu initial snapshot được chỉ định, chỉ changes kể từ snapshot đó được bao gồm; nếu không, bất kỳ regions nào của image chứa data được bao gồm. End snapshot được chỉ định bằng tùy chọn –snap hoặc syntax @snap (xem bên dưới). Image diff format bao gồm metadata về image size changes, và start và end snapshots. Nó đại diện hiệu quả cho discarded hoặc 'zero' regions của image.

### feature
- `feature disable image-spec feature-name…`: Tắt tính năng được chỉ định trên image được chỉ định. Có thể chỉ định nhiều tính năng.
- `feature enable image-spec feature-name…`: Bật tính năng được chỉ định trên image được chỉ định. Có thể chỉ định nhiều tính năng.

### flatten
```
flatten image-spec
```
Nếu image là clone, copy tất cả shared blocks từ parent snapshot và làm cho child độc lập với parent, cắt đứt liên kết giữa parent snap và child. Parent snapshot có thể được unprotect và xóa nếu nó không có dependent cloned children nào khác.

Yêu cầu image format 2.

### group
- `group create group-spec`: Tạo group.
- `group image add group-spec image-spec`: Thêm image vào group.
- `group image list group-spec`: Liệt kê images trong group.
- `group image remove group-spec image-spec`: Xóa image khỏi group.
- `group ls [-p | –pool pool-name]`: Liệt kê rbd groups.
- `group rename src-group-spec dest-group-spec`: Đổi tên group. Lưu ý: rename across pools không được hỗ trợ.
- `group rm group-spec`: Xóa group.
- `group snap create group-snap-spec`: Tạo snapshot của group.
- `group snap list group-spec`: Liệt kê snapshots của group.
- `group snap rm group-snap-spec`: Xóa snapshot khỏi group.
- `group snap rename group-snap-spec snap-name`: Đổi tên snapshot của group.
- `group snap rollback group-snap-spec`: Rollback group to snapshot.

### image-meta
- `image-meta get image-spec key`: Lấy giá trị metadata với key.
- `image-meta list image-spec`: Hiển thị metadata được giữ trên image. Cột đầu là key và cột thứ hai là value.
- `image-meta remove image-spec key`: Xóa metadata key với value.
- `image-meta set image-spec key value`: Đặt metadata key với value. Chúng sẽ được hiển thị trong image-meta list.

### import
```
import [–export-format format (1 or 2)] [–image-format format-id] [–object-size size-in-B/K/M] [–stripe-unit size-in-B/K/M –stripe-count num] [–image-feature feature-name]… [–image-shared] src-path [image-spec]
```
Tạo image mới và import data của nó từ path (sử dụng - cho stdin). Import operation sẽ cố gắng tạo sparse rbd images nếu có thể. Đối với import từ stdin, sparsification unit là data block size của destination image (object size).

Các tùy chọn –stripe-unit và –stripe-count là tùy chọn, nhưng phải được sử dụng cùng nhau.

–export-format chấp nhận '1' hoặc '2' hiện tại. Format 2 cho phép import không chỉ nội dung của image, mà còn snapshots và các properties khác, như image_order, features.

### import-diff
```
import-diff src-path image-spec
```
Import incremental diff của image và áp dụng nó vào current image. Nếu diff được tạo relative to start snapshot, chúng tôi verify snapshot đó đã tồn tại trước khi tiếp tục. Nếu có end snapshot chúng tôi verify nó chưa tồn tại trước khi áp dụng changes, và tạo snapshot khi chúng tôi hoàn thành.

### info
```
info image-spec | snap-spec
```
Sẽ dump thông tin (như size và object size) về specific rbd image. Nếu image là clone, thông tin về parent của nó cũng được hiển thị. Nếu snapshot được chỉ định, có được protect hay không được hiển thị.

### journal
- `journal client disconnect journal-spec`: Flag image journal client là disconnected.
- `journal export [–verbose] [–no-error] src-journal-spec path-name`: Export image journal to path (sử dụng - cho stdout). Nó có thể tạo backup của image journal đặc biệt trước khi thực hiện dangerous operations.
- `journal import [–verbose] [–no-error] path-name dest-journal-spec`: Import image journal từ path (sử dụng - cho stdin).
- `journal info journal-spec`: Hiển thị thông tin về image journal.
- `journal inspect [–verbose] journal-spec`: Inspect và report image journal cho structural errors.
- `journal reset journal-spec`: Reset image journal.
- `journal status journal-spec`: Hiển thị status của image journal.

### lock
- `lock add [–shared lock-tag] image-spec lock-id`: Khóa image. lock-id là tên tùy ý cho convenience của user. Theo mặc định, đây là exclusive lock, nghĩa là nó sẽ fail nếu image đã được khóa. Tùy chọn –shared thay đổi behavior này. Lưu ý rằng locking không ảnh hưởng đến bất kỳ operation nào khác ngoài adding lock. Nó không bảo vệ image khỏi bị xóa.
- `lock ls image-spec`: Hiển thị locks được giữ trên image. Cột đầu là locker để sử dụng với lệnh lock remove.
- `lock rm image-spec lock-id locker`: Release lock trên image. lock id và locker là như output bởi lock ls.

### ls
```
ls [-l | –long] [pool-name]
```
Sẽ liệt kê tất cả rbd images được liệt kê trong rbd_directory object. Với -l, cũng show snapshots, và sử dụng longer-format output bao gồm size, parent (nếu clone), format, etc.

### merge-diff
```
merge-diff first-diff-path second-diff-path merged-diff-path
```
Merge hai continuous incremental diffs của image thành một single diff. First diff's end snapshot phải bằng với second diff's start snapshot. First diff có thể là - cho stdin, và merged diff có thể là - cho stdout, cho phép multiple diff files được merge bằng cách sử dụng something like 'rbd merge-diff first second - | rbd merge-diff - third result'. Lưu ý command này hiện tại chỉ support source incremental diff với stripe_count == 1.

### migration
- `migration abort image-spec`: Hủy image migration. Step này có thể được run sau successful hoặc failed migration prepare hoặc migration execute steps và trả image về state ban đầu (trước migration). Tất cả modifications to destination image bị mất.
- `migration commit image-spec`: Commit image migration. Step này được run sau successful migration prepare và migration execute steps và removes source image data.
- `migration execute image-spec`: Execute image migration. Step này được run sau successful migration prepare step và copies image data to destination.
- `migration prepare [–order order] [–object-size object-size] [–image-feature image-feature] [–image-shared] [–stripe-unit stripe-unit] [–stripe-count stripe-count] [–data-pool data-pool] [–import-only] [–source-spec json] [–source-spec-path path] src-image-spec [dest-image-spec]`: Prepare image migration. Đây là first step khi migrating image, tức là changing image location, format hoặc parameters khác không thể thay đổi dynamically. Destination có thể match source, và trong trường hợp đó dest-image-spec có thể được omit. Sau step này, source image được set là parent của destination image, và image accessible trong copy-on-write mode bởi destination spec của nó.

Image cũng có thể được migrated từ read-only import source bằng cách thêm optional –import-only và providing JSON-encoded –source-spec hoặc path to JSON-encoded source-spec file bằng –source-spec-path optionals.

### mirror
- `mirror image demote image-spec`: Demote primary image thành non-primary cho RBD mirroring.
- `mirror image disable [–force] image-spec`: Tắt RBD mirroring cho image. Nếu mirroring được config trong `image` mode cho image's pool, thì nó có thể được explicitly disable mirroring cho mỗi image trong pool.
- `mirror image enable image-spec mode`: Bật RBD mirroring cho image. Nếu mirroring được config trong `image` mode cho image's pool, thì nó có thể được explicitly enable mirroring cho mỗi image trong pool.

Mirror image mode có thể là `journal` (mặc định) hoặc `snapshot`. `journal` mode yêu cầu RBD journaling feature.

- `mirror image promote [–force] image-spec`: Promote non-primary image thành primary cho RBD mirroring.
- `mirror image resync image-spec`: Force resync to primary image cho RBD mirroring.
- `mirror image status image-spec`: Hiển thị RBD mirroring status cho image.
- `mirror pool demote [pool-name]`: Demote tất cả primary images trong pool thành non-primary. Mọi mirroring enabled image sẽ demoted trong pool.
- `mirror pool disable [pool-name]`: Tắt RBD mirroring theo mặc định trong pool. Khi mirroring bị tắt trên pool theo cách này, mirroring cũng sẽ bị tắt trên bất kỳ images nào (trong pool) mà mirroring đã được enable explicitly.
- `mirror pool enable [pool-name] mode`: Bật RBD mirroring theo mặc định trong pool. Mirroring mode có thể là `pool` hoặc `image`. Nếu config trong `pool` mode, tất cả images trong pool với journaling feature enabled được mirrored. Nếu config trong `image` mode, mirroring cần được explicitly enable (bởi `mirror` `image` `enable` command) trên mỗi image.
- `mirror pool info [pool-name]`: Hiển thị thông tin về pool mirroring configuration. Nó bao gồm mirroring mode, peer UUID, remote cluster name, và remote client name.
- `mirror pool peer add [pool-name] remote-cluster-spec`: Thêm mirroring peer vào pool. remote-cluster-spec là [remote client name@]remote cluster name.

Mặc định cho remote client name là "client.admin".

Điều này yêu cầu mirroring mode được enable.

- `mirror pool peer remove [pool-name] uuid`: Xóa mirroring peer khỏi pool. Peer uuid available từ `mirror` `pool` `info` command.
- `mirror pool peer set [pool-name] uuid key value`: Cập nhật mirroring peer settings. Key có thể là `client` hoặc `cluster`, và value tương ứng với remote client name hoặc remote cluster name.
- `mirror pool promote [–force] [pool-name]`: Promote tất cả non-primary images trong pool thành primary. Mọi mirroring enabled image sẽ promoted trong pool.
- `mirror pool status [–verbose] [pool-name]`: Hiển thị status cho tất cả mirrored images trong pool. Với –verbose, cũng output additionally status details cho mọi mirroring image trong pool.
- `mirror snapshot schedule add [-p | –pool pool] [–namespace namespace] [–image image] interval [start-time]`: Thêm mirror snapshot schedule.
- `mirror snapshot schedule list [-R | –recursive] [–format format] [–pretty-format] [-p | –pool pool] [–namespace namespace] [–image image]`: Liệt kê mirror snapshot schedule.
- `mirror snapshot schedule remove [-p | –pool pool] [–namespace namespace] [–image image] interval [start-time]`: Xóa mirror snapshot schedule.
- `mirror snapshot schedule status [-p | –pool pool] [–format format] [–pretty-format] [–namespace namespace] [–image image]`: Hiển thị mirror snapshot schedule status.

### mv
```
mv src-image-spec dest-image-spec
```
Đổi tên image. Lưu ý: rename across pools không được hỗ trợ.

### namespace
- `namespace create pool-name/namespace-name`: Tạo namespace image mới trong pool.
- `namespace list pool-name`: Liệt kê image namespaces được định nghĩa trong pool.
- `namespace remove pool-name/namespace-name`: Xóa empty image namespace khỏi pool.

### object-map
- `object-map check image-spec | snap-spec`: Verify object map là correct.
- `object-map rebuild image-spec | snap-spec`: Rebuild invalid object map cho specified image. Image snapshot có thể được chỉ định để rebuild invalid object map cho snapshot.

### pool init
```
pool init [pool-name] [–force]
```
Khởi tạo pool để sử dụng bởi RBD. Newly created pools phải initialized trước khi sử dụng.

### resize
```
resize (-s | –size size-in-M/G/T) [–allow-shrink] image-spec
```
Resize rbd image. Tham số size cũng cần được chỉ định. Tùy chọn –allow-shrink cho phép size được giảm.

### rm
```
rm image-spec
```
Xóa rbd image (bao gồm tất cả data blocks). Nếu image có snapshots, điều này fail và không có gì bị xóa.

### snap
- `snap create snap-spec`: Tạo snapshot mới. Yêu cầu snapshot name parameter được chỉ định.
- `snap limit clear image-spec`: Xóa bất kỳ limit nào đã được set trước đó về số lượng snapshots được phép trên image.
- `snap limit set [–limit] limit image-spec`: Đặt limit cho số lượng snapshots được phép trên image.
- `snap ls image-spec`: Dump danh sách snapshots bên trong specific image.
- `snap protect snap-spec`: Bảo vệ snapshot khỏi deletion, để clones có thể được tạo của nó (xem rbd clone). Snapshots phải được protect trước khi clones được tạo; protection implies rằng có dependent cloned children refer to snapshot này. rbd clone sẽ fail trên nonprotected snapshot.

Yêu cầu image format 2.

- `snap purge image-spec`: Xóa tất cả unprotected snapshots từ image.
- `snap rename src-snap-spec dest-snap-spec`: Đổi tên snapshot. Lưu ý: rename across pools và images không được hỗ trợ.
- `snap rm [–force] snap-spec`: Xóa specified snapshot.
- `snap rollback snap-spec`: Rollback image content to snapshot. Điều này sẽ iterate qua toàn bộ blocks array và update data head content to snapshotted version.
- `snap unprotect snap-spec`: Unprotect snapshot từ deletion (undo snap protect). Nếu cloned children vẫn còn, snap unprotect fails. (Lưu ý rằng clones có thể tồn tại trong different pools hơn parent snapshot.)

Yêu cầu image format 2.

### sparsify
```
sparsify [–sparse-size sparse-size] image-spec
```
Reclaim space cho zeroed image extents. Sparse size mặc định là 4096 bytes và có thể được thay đổi qua –sparse-size option với các restrictions sau: nó nên là power of two, không nhỏ hơn 4096, và không lớn hơn image object size.

### status
```
status image-spec
```
Hiển thị status của image, bao gồm clients nào có nó open.

### trash
- `trash ls [pool-name]`: Liệt kê tất cả entries từ trash.
- `trash mv image-spec`: Di chuyển image to trash. Images, ngay cả những cái actively in-use bởi clones, có thể được move to trash và deleted tại later time.
- `trash purge [pool-name]`: Xóa tất cả expired images từ trash.
- `trash restore image-id`: Restore image từ trash.
- `trash rm image-id`: Xóa image từ trash. Nếu image deferment time chưa expire bạn không thể removed nó trừ khi use force. Nhưng actively in-use bởi clones hoặc has snapshots không thể removed.
- `trash purge schedule add [-p | –pool pool] [–namespace namespace] interval [start-time]`: Thêm trash purge schedule.
- `trash purge schedule list [-R | –recursive] [–format format] [–pretty-format] [-p | –pool pool] [–namespace namespace]`: Liệt kê trash purge schedule.
- `trash purge schedule remove [-p | –pool pool] [–namespace namespace] interval [start-time]`: Xóa trash purge schedule.
- `trash purge schedule status [-p | –pool pool] [–format format] [–pretty-format] [–namespace namespace]`: Hiển thị trash purge schedule status.

### watch
```
watch image-spec
```
Watch events trên image.

## Image, Snap, Group và Journal Specs

image-spec là [pool-name/[namespace-name/]]image-name  
snap-spec là [pool-name/[namespace-name/]]image-name@snap-name  
group-spec là [pool-name/[namespace-name/]]group-name  
group-snap-spec là [pool-name/[namespace-name/]]group-name@snap-name  
journal-spec là [pool-name/[namespace-name/]]journal-name  

Mặc định cho pool-name là "rbd" và namespace-name là "". Nếu image name chứa ký tự slash ('/'), pool-name là bắt buộc.

Journal-name là image-id.

Bạn có thể chỉ định từng name individually, sử dụng –pool, –namespace, –image, và –snap options, nhưng điều này được khuyến khích chống lại ủng hộ spec syntax ở trên.

## Striping

RBD images được stripe qua nhiều objects, sau đó được lưu trữ bởi Ceph distributed object store (RADOS). Kết quả, read và write requests cho image được phân tán qua nhiều nodes trong cluster, thường ngăn bất kỳ single node nào trở thành bottleneck khi individual images trở nên lớn hoặc busy.

Striping được kiểm soát bởi ba parameters:

- **object-size**: Kích thước của objects chúng ta stripe qua là power of two. Nó sẽ được làm tròn lên nearest power of two. Object size mặc định là 4 MB, nhỏ nhất là 4K và tối đa là 32M.
- **stripe_unit**: Mỗi [stripe_unit] contiguous bytes được lưu trữ adjacently trong cùng object, trước khi chúng ta move on đến next object.
- **stripe_count**: Sau khi chúng ta write [stripe_unit] bytes to [stripe_count] objects, chúng ta loop back to initial object và write another stripe, cho đến khi object đạt maximum size của nó. Tại thời điểm đó, chúng ta move on đến next [stripe_count] objects.

Theo mặc định, [stripe_unit] giống như object size và [stripe_count] là 1. Chỉ định khác [stripe_unit] và/hoặc [stripe_count] thường được gọi là sử dụng "fancy" striping và yêu cầu format 2.

## Kernel RBD (KRBD) Options

Hầu hết các options này chỉ hữu ích mainly cho debugging và benchmarking. Các giá trị mặc định được set trong kernel và do đó có thể phụ thuộc vào version của running kernel.

### Per client instance rbd device map options:

- fsid=aaaaaaaa-bbbb-cccc-dddd-eeeeeeeeeeee - FSID mà client nên assume.
- ip=a.b.c.d[:p] - IP và, optionally, port mà client nên use.
- share - Enable sharing của client instances với other mappings (mặc định).
- noshare - Disable sharing của client instances với other mappings.
- crc - Enable CRC32C checksumming cho msgr1 on-the-wire protocol (mặc định). Cho msgr2.1 protocol option này ignored: full checksumming luôn on trong 'crc' mode và luôn off trong 'secure' mode.
- nocrc - Disable CRC32C checksumming cho msgr1 on-the-wire protocol. Lưu ý rằng chỉ payload checksumming bị disable, header checksumming luôn on. Cho msgr2.1 protocol option này ignored.
- cephx_require_signatures - Require msgr1 message signing feature (từ 3.19, mặc định). Option này deprecated và sẽ được removed trong future vì feature đã được support từ Bobtail release.
- nocephx_require_signatures - Don't require msgr1 message signing feature (từ 3.19). Option này deprecated và sẽ được removed trong future.
- tcp_nodelay - Disable Nagle's algorithm trên client sockets (từ 4.0, mặc định).
- notcp_nodelay - Enable Nagle's algorithm trên client sockets (từ 4.0).
- cephx_sign_messages - Enable message signing cho msgr1 on-the-wire protocol (từ 4.4, mặc định). Cho msgr2.1 protocol option này ignored: message signing built into 'secure' mode và not offered trong 'crc' mode.
- nocephx_sign_messages - Disable message signing cho msgr1 on-the-wire protocol (từ 4.4). Cho msgr2.1 protocol option này ignored.
- mount_timeout=x - Timeout trên various steps trong rbd device map và rbd device unmap sequences (mặc định là 60 seconds). Đặc biệt, từ 4.2 điều này có thể được use để ensure rằng rbd device unmap eventually times out khi không có network connection to cluster.
- osdkeepalive=x - OSD keepalive timeout (mặc định là 5 seconds).
- osd_idle_ttl=x - OSD idle TTL (mặc định là 60 seconds).

### Per mapping (block device) rbd device map options:

- rw - Map image read-write (mặc định). Overridden bởi –read-only.
- ro - Map image read-only. Equivalent to –read-only.
- queue_depth=x - queue depth (từ 4.2, mặc định là 128 requests).
- lock_on_read - Acquire exclusive lock trên reads, ngoài writes và discards (từ 4.9).
- exclusive - Disable automatic exclusive lock transitions (từ 4.12). Equivalent to –exclusive.
- lock_timeout=x - Timeout trên waiting cho acquisition của exclusive lock (từ 4.17, mặc định là 0 seconds, nghĩa là no timeout).
- notrim - Turn off discard và write zeroes offload support để avoid deprovisioning fully provisioned image (từ 4.17). Khi enabled, discard requests sẽ fail với -EOPNOTSUPP, write zeroes requests sẽ fall back to manually zeroing.
- abort_on_full - Fail write requests với -ENOSPC khi cluster full hoặc data pool reaches quota (từ 5.0). Default behaviour là block cho đến khi full condition cleared.
- alloc_size - Minimum allocation unit của underlying OSD object store backend (từ 5.1, mặc định là 64K bytes). Được use để round off và drop discards quá small. Cho bluestore, recommended setting là bluestore_min_alloc_size (hiện tại set to 4K cho tất cả types of drives, previously used to be set to 64K cho hard disk drives và 16K cho solid-state drives). Cho filestore với filestore_punch_hole = false, recommended setting là image object size (typically 4M).
- crush_location=x - Chỉ định location của client trong terms of CRUSH hierarchy (từ 5.8). Đây là set of key-value pairs separated từ each other bởi '|', với keys separated từ values bởi ':'. Lưu ý rằng '|' có thể need to be quoted hoặc escaped để avoid interpreted as pipe bởi shell. Key là bucket type name (e.g. rack, datacenter hoặc region với default bucket types) và value là bucket name. Ví dụ, để indicate rằng client local to rack "myrack", datacenter "mydc" và region "myregion":

crush_location=rack:myrack|datacenter:mydc|region:myregion

Mỗi key-value pair đứng on its own: "myrack" doesn't need to reside in "mydc", which in turn doesn't need to reside in "myregion". Location không phải là path to root của hierarchy nhưng rather set of nodes matched independently, owning to fact rằng bucket names unique within CRUSH map.

"Multipath" locations được support, so có thể indicate locality cho multiple parallel hierarchies:

crush_location=rack:myrack1|rack:myrack2|datacenter:mydc

- read_from_replica=no - Disable replica reads, luôn pick primary OSD (từ 5.8, mặc định).
- read_from_replica=balance - Khi issued read trên replicated pool, pick random OSD cho serving it (từ 5.8).

Mode này safe cho general use chỉ since Octopus (tức là after "ceph osd require-osd-release octopus"). Otherwise nó should be limited to read-only workloads như images mapped read-only everywhere hoặc snapshots.

- read_from_replica=localize - Khi issued read trên replicated pool, pick most local OSD cho serving it (từ 5.8). Locality metric calculated against location của client given với crush_location; match với lowest-valued bucket type wins. Ví dụ, với default bucket types, OSD in matching rack closer than OSD in matching datacenter, which in turn closer than OSD in matching region.

Mode này safe cho general use chỉ since Octopus (tức là after "ceph osd require-osd-release octopus"). Otherwise nó should be limited to read-only workloads như images mapped read-only everywhere hoặc snapshots.

- compression_hint=none - Don't set compression hints (từ 5.8, mặc định).
- compression_hint=compressible - Hint to underlying OSD object store backend rằng data compressible, enabling compression in passive mode (từ 5.8).
- compression_hint=incompressible - Hint to underlying OSD object store backend rằng data incompressible, disabling compression in aggressive mode (từ 5.8).
- ms_mode=legacy - Use msgr1 on-the-wire protocol (từ 5.11, mặc định).
- ms_mode=crc - Use msgr2.1 on-the-wire protocol, select 'crc' mode, also referred to as plain mode (từ 5.11). Nếu daemon denies 'crc' mode, fail connection.
- ms_mode=secure - Use msgr2.1 on-the-wire protocol, select 'secure' mode (từ 5.11). 'secure' mode provides full in-transit encryption ensuring both confidentiality và authenticity. Nếu daemon denies 'secure' mode, fail connection.
- ms_mode=prefer-crc - Use msgr2.1 on-the-wire protocol, select 'crc' mode (từ 5.11). Nếu daemon denies 'crc' mode in favor of 'secure' mode, agree to 'secure' mode.
- ms_mode=prefer-secure - Use msgr2.1 on-the-wire protocol, select 'secure' mode (từ 5.11). Nếu daemon denies 'secure' mode in favor of 'crc' mode, agree to 'crc' mode.
- rxbounce - Use bounce buffer khi receiving data (từ 5.17). Default behaviour là read directly into destination buffer. Bounce buffer needed nếu destination buffer không guaranteed to be stable (tức là remain unchanged while being read to). Đặc biệt, đây là case cho Windows where system-wide "dummy" (throwaway) page có thể be mapped into destination buffer để generate single large I/O. Otherwise, "libceph: … bad crc/signature" hoặc "libceph: … integrity error, bad crc" errors và associated performance degradation expected.
- udev - Wait cho udev device manager to finish executing all matching "add" rules và release device trước khi exiting (mặc định). Option này not passed to kernel.
- noudev - Don't wait cho udev device manager. Khi enabled, device may not be fully usable immediately on exit.

### rbd device unmap options:

- force - Force unmapping của block device đang open (từ 4.9). Driver sẽ wait cho running requests to complete và then unmap; requests sent to driver after initiating unmap sẽ be failed.
- udev - Wait cho udev device manager to finish executing all matching "remove" rules và clean up after device trước khi exiting (mặc định). Option này not passed to kernel.
- noudev - Don't wait cho udev device manager.

## Ví dụ

Để tạo RBD image mới là 100 GB:

```
rbd create mypool/myimage --size 102400
```

Để sử dụng non-default object size (8 MB):

```
rbd create mypool/myimage --size 102400 --object-size 8M
```

Để xóa RBD image (cẩn thận!):

```
rbd rm mypool/myimage
```

Để tạo snapshot mới:

```
rbd snap create mypool/myimage@mysnap
```

Để tạo copy-on-write clone của protected snapshot:

```
rbd clone mypool/myimage@mysnap otherpool/cloneimage
```

Để xem clones nào của snapshot tồn tại:

```
rbd children mypool/myimage@mysnap
```

Để xóa snapshot:

```
rbd snap rm mypool/myimage@mysnap
```

Để map image qua kernel với cephx enabled:

```
rbd device map mypool/myimage --id admin --keyfile secretfile
```

Để map image qua kernel với different cluster name other than default ceph:

```
rbd device map mypool/myimage --cluster cluster-name
```

Để unmap image:

```
rbd device unmap /dev/rbd0
```

Để tạo image và clone từ nó:

```
rbd import --image-format 2 image mypool/parent
rbd snap create mypool/parent@snap
rbd snap protect mypool/parent@snap
rbd clone mypool/parent@snap otherpool/child
```

Để tạo image với smaller stripe_unit (để better distribute small writes trong some workloads):

```
rbd create mypool/myimage --size 102400 --stripe-unit 65536B --stripe-count 16
```

Để change image từ one image format sang another, export nó và then import as desired image format:

```
rbd export mypool/myimage@snap /tmp/img
rbd import --image-format 2 /tmp/img mypool/myimage2
```

Để lock image cho exclusive use:

```
rbd lock add mypool/myimage mylockid
```

Để release lock:

```
rbd lock remove mypool/myimage mylockid client.2485
```

Để list images từ trash:

```
rbd trash ls mypool
```

Để defer delete image (use –expires-at để set expiration time, default là now):

```
rbd trash mv mypool/myimage --expires-at "tomorrow"
```

Để xóa image từ trash (cẩn thận!):

```
rbd trash rm mypool/myimage-id
```

Để force delete image từ trash (cẩn thận!):

```
rbd trash rm mypool/myimage-id --force
```

Để restore image từ trash:

```
rbd trash restore mypool/myimage-id
```

Để restore image từ trash và rename nó:

```
rbd trash restore mypool/myimage-id --image mynewimage
```

## Availability

rbd là part of Ceph, massively scalable, open-source, distributed storage system. Please refer to Ceph documentation at http://ceph.com/docs for more information.

## See also

ceph(8), rados(8)