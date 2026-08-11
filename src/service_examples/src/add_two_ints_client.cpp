#include <chrono>
#include <cstdlib>
#include <memory>

#include "example_msgs/srv/add_two_int.hpp"
#include "rclcpp/rclcpp.hpp"

using AddTwoInt = example_msgs::srv::AddTwoInt;
using namespace std::chrono_literals;

class AddTwoIntsClient : public rclcpp::Node
{
public:
  AddTwoIntsClient() : Node("add_two_ints_client")
  {
    client_ = create_client<AddTwoInt>("add_two_ints");
  }

  bool send_request(int64_t a, int64_t b)
  {
    while (!client_->wait_for_service(1s)) {
      if (!rclcpp::ok()) {
        RCLCPP_ERROR(get_logger(), "Interrupted while waiting for the service");
        return false;
      }

      RCLCPP_INFO(get_logger(), "Waiting for service...");
    }

    auto request = std::make_shared<AddTwoInt::Request>();
    request->a = a;
    request->b = b;

    auto future = client_->async_send_request(request);

    if (rclcpp::spin_until_future_complete(shared_from_this(), future) !=
      rclcpp::FutureReturnCode::SUCCESS)
    {
      RCLCPP_ERROR(get_logger(), "Service call failed");
      return false;
    }

    RCLCPP_INFO(get_logger(), "Result: %ld", future.get()->c);
    return true;
  }

private:
  rclcpp::Client<AddTwoInt>::SharedPtr client_;
};

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

  auto node = std::make_shared<AddTwoIntsClient>();
  const bool success = node->send_request(std::atoll(argv[1]), std::atoll(argv[2]));

  rclcpp::shutdown();
  return success ? 0 : 1;
}
