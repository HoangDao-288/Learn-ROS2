#include <chrono>
#include <cstdlib>
#include <memory>

#include "example_msgs/srv/add_two_int.hpp"
#include "rclcpp/rclcpp.hpp"

using AddTwoInt = example_msgs::srv::AddTwoInt;
using namespace std::chrono_literals;

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  if (argc != 3) {
    RCLCPP_ERROR(
      rclcpp::get_logger("add_two_ints_client"),
      "Usage: add_two_ints_client <a> <b>");
    rclcpp::shutdown();
    return 1;
  }

  auto node = rclcpp::Node::make_shared("add_two_ints_client");
  auto client = node->create_client<AddTwoInt>("add_two_ints");

  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(node->get_logger(), "Interrupted while waiting for the service");
      rclcpp::shutdown();
      return 1;
    }

    RCLCPP_INFO(node->get_logger(), "Waiting for service...");
  }

  auto request = std::make_shared<AddTwoInt::Request>();
  request->a = std::atoll(argv[1]);
  request->b = std::atoll(argv[2]);

  auto future = client->async_send_request(request);

  if (rclcpp::spin_until_future_complete(node, future) !=
    rclcpp::FutureReturnCode::SUCCESS)
  {
    RCLCPP_ERROR(node->get_logger(), "Service call failed");
    rclcpp::shutdown();
    return 1;
  }

  RCLCPP_INFO(node->get_logger(), "Result: %ld", future.get()->c);

  rclcpp::shutdown();
  return 0;
}
