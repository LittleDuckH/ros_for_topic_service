#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/srv/money.hpp"
#include <iostream>

using std::placeholders::_1;

class MinimalClienter : public rclcpp::Node
{
public:
  MinimalClienter(): Node("client_test")
  {
    money_client = this->create_client<tutorial_interfaces::srv::Money>("service_node");
  }

  void send_client(char * argv[])
  {

    RCLCPP_INFO(this->get_logger(), "ready to get the request!!!");
    // 请求上线
    while (!money_client->wait_for_service(std::chrono::seconds(1)))
    {
      RCLCPP_WARN(this->get_logger(), "waitting for the service!");
    }
    // 请求数据
    auto request = std::make_shared<tutorial_interfaces::srv::Money::Request>();
    request->name = std::string(argv[1]);
    request->money = std::stoul(argv[2]);
    // 发送异步请求
    money_client->async_send_request(request, std::bind(&MinimalClienter::client_callback,this,_1));
    std::exit(0);
  }

private:
  void client_callback(rclcpp::Client<tutorial_interfaces::srv::Money>::SharedFuture response)
  {
    auto result = response.get();
    RCLCPP_INFO(this->get_logger(), "result_success = %d\n result_money = %d", result->success, result->money);

    if(result->success)
    {
      RCLCPP_INFO(this->get_logger(), "get the money successfully!!!");
    }else
    {
      RCLCPP_INFO(this->get_logger(), "get the money failed!!!");
    }
    
  }
  
  rclcpp::Client<tutorial_interfaces::srv::Money>::SharedPtr money_client;


};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  if (argc != 3) {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "usage: add_two_ints_client string uint32");
    return 1;
  }
  auto node = std::make_shared<MinimalClienter>();
  node->send_client(argv);
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}