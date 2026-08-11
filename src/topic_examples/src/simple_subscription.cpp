#include "../include/simple_subscription.hpp"

SimpleSubscription::SimpleSubscription(const std::string &node_name) : rclcpp::Node(node_name)
{
    RCLCPP_INFO(this->get_logger(), "Init Subscription node");
    sub_ = create_subscription<std_msgs::msg::String>(
        "/topic_1", 
        rclcpp::QoS(10).best_effort(), 
        [this](const std_msgs::msg::String &msg)
        {
            this->msgCallback(msg);
        }
    );
}

void SimpleSubscription::msgCallback(const std_msgs::msg::String &msg)
{
    RCLCPP_INFO_STREAM(this->get_logger(), "Data received: " << msg.data);
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SimpleSubscription>();
    rclcpp::spin(node);
    rclcpp::shutdown();
}