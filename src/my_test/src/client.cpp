#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("simple_client");
    auto client = node->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");

    // 1. 等待服务上线
    while (!client->wait_for_service(std::chrono::seconds(1))) {
        if (!rclcpp::ok()) return 0;
        RCLCPP_INFO(node->get_logger(), "等待服务端...");
    }

    // 2. 构造请求数据 (5 + 10)
    auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
    request->a = 5;
    request->b = 10;

    // 3. 发送并等待结果
    auto result_future = client->async_send_request(request);
    if (rclcpp::spin_until_future_complete(node, result_future) == rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(node->get_logger(), "结果: %ld", result_future.get()->sum);
    }

    rclcpp::shutdown();
    return 0;
}
