# Tạo Simple Publisher mỗi 1s publish 1 tick ra topic /topic

- Include thư viện rclcpp
- Tạo node bằng cách tạo 1 class SimplePublisher kế thừa class Node
- Trong hàm khởi tạo của class, tạo publisher và timer (cứ mỗi 1s thì gọi hàm callback)
-Hàm callback publish data đến topic /topic