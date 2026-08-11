#include <functional>
#include <memory>

#include "example_msgs/srv/add_two_int.hpp"
#include "rclcpp/rclcpp.hpp"

using AddTwoInt = example_msgs::srv::AddTwoInt;

class AddTwoIntsServer : public rclcpp::Node
{
public:
  AddTwoIntsServer()
  : Node("add_two_ints_server")
  {
    service_ = create_service<AddTwoInt>(
      "add_two_ints",
      std::bind(
        &AddTwoIntsServer::add_two_ints,
        this,
        std::placeholders::_1,
        std::placeholders::_2));

    RCLCPP_INFO(get_logger(), "AddTwoInt service is ready");
  }

private:
  void add_two_ints(
    const std::shared_ptr<AddTwoInt::Request> request,
    std::shared_ptr<AddTwoInt::Response> response)
  {
    response->c = request->a + request->b;
  }

  rclcpp::Service<AddTwoInt>::SharedPtr service_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<AddTwoIntsServer>();
  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}
