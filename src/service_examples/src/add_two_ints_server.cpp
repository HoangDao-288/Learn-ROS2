#include <memory>

#include "example_msgs/srv/add_two_int.hpp"
#include "rclcpp/rclcpp.hpp"

using AddTwoInt = example_msgs::srv::AddTwoInt;

void add_two_ints(
  const std::shared_ptr<AddTwoInt::Request> request,
  std::shared_ptr<AddTwoInt::Response> response)
{
  response->c = request->a + request->b;
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node = rclcpp::Node::make_shared("add_two_ints_server");
  auto service = node->create_service<AddTwoInt>("add_two_ints", &add_two_ints);

  RCLCPP_INFO(node->get_logger(), "AddTwoInt service is ready");
  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}
