#ifndef SIMPLE_PUBLISHER_H
#define SIMPLE_PUBLISHER_H

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <chrono>
#include <functional>
#include <memory>
#include <string>

class SimplePublisher : public rclcpp::Node
{
public:
  // explicit SimplePublisher(const std::string & node_name = "simple_publisher");
  SimplePublisher();

private:
  void timer_callback();
  void msg_callback(const std_msgs::msg::String &msg);

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
  rclcpp::TimerBase::SharedPtr timer_;
  unsigned int counter_;
};

#endif  // SIMPLE_PUBLISHER_H
