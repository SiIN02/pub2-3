#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <memory>
#include <chrono>
#include <functional>
//#include <string>
using namespace std::chrono_literals;

void callback(rclcpp::Node::SharedPtr node, rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub)
{
    geometry_msgs::msg::Twist message;
    message.linear.x = 3.14;
    message.angular.z = -1.57;
    pub->publish(message);
    RCLCPP_INFO(node->get_logger(), "data : line 3.14, ang 1.57");
    //rclcpp::spin_some(node);
    //loop_rate.sleep(); //반복주파수에서 남은 시간 만큼 sleep
}

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("mynode");
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    auto pub = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", qos_profile);  //노드명 mytopic -> 터틀봇 노드로변경
    std::function<void()> fn = std::bind(callback, node, pub);
    auto timer = node->create_wall_timer(100ms, fn);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}