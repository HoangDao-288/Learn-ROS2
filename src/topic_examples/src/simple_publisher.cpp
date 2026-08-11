#include "simple_publisher.h"

// SimplePublisher::SimplePublisher(const std::string & node_name)
// : rclcpp::Node(node_name), counter_(0)
SimplePublisher::SimplePublisher() : rclcpp::Node("pub_node"), counter_(0)
{
  pub_ = this->create_publisher<std_msgs::msg::String>(
    "/topic",
    rclcpp::QoS(10).best_effort());
  timer_ = this->create_wall_timer(
    std::chrono::seconds(1),
    std::bind(&SimplePublisher::timer_callback, this));

  sub_ = create_subscription<std_msgs::msg::String>(
    "/topic",
    rclcpp::QoS(10).best_effort(),
    [this](const std_msgs::msg::String &msg)
    {
      this->msg_callback(msg);
    }
  );

  RCLCPP_INFO(this->get_logger(), "Initialized SimplePublisher node");
}

void SimplePublisher::timer_callback()
{
  rclcpp::Time timestamp = this->get_clock()->now();
  std_msgs::msg::String msg;
  msg.data ="[" + std::to_string(timestamp.seconds()) + "] Tick: " + std::to_string(counter_);
  pub_->publish(msg);
  counter_++;
}

void SimplePublisher::msg_callback(const std_msgs::msg::String &msg)
{
  RCLCPP_INFO_STREAM(this->get_logger(), "Data received: " << msg.data);
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<SimplePublisher>();
  rclcpp::executors::SingleThreadedExecutor executor;
  executor.add_node(node);
  executor.spin();

  rclcpp::shutdown();
  return 0;
}
