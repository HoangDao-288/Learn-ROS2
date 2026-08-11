#ifndef SIMPLE_SUBCRIPTION_H
#define SIMPLE_SUBCRIPTION_H

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <string>

class SimpleSubscription : public rclcpp::Node
{
public:
    explicit SimpleSubscription(const std::string &node_name = "sub_node");
private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
    void msgCallback(const std_msgs::msg::String &msg);

};

#endif // SIMPLE_SUPCRIPTION