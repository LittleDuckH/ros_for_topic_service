#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/srv/money.hpp"

#include <iostream>

using namespace std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;

class MinimalServicer : public rclcpp::Node
{
public:
  MinimalServicer(): Node("service_test")
  {
    money_service_callbackgroup = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);

    money_service = this->create_service<tutorial_interfaces::srv::Money>("service_node", std::bind(&MinimalServicer::service_callback, this, _1, _2),
                                                                          rmw_qos_profile_services_default,
                                                                          money_service_callbackgroup);
  }



private:

  void service_callback(const tutorial_interfaces::srv::Money::Request::SharedPtr request, const tutorial_interfaces::srv::Money::Response::SharedPtr response)
  {
    RCLCPP_INFO(this->get_logger(), "get a service that request\n name is %s \n money is %d", request->name.c_str(), request->money);
    rclcpp::Rate rate(1);
    if(request->money > 100)
    {
      response->success = true;
      response->money = request->money;
      rate.sleep();
      RCLCPP_INFO(this->get_logger(), "OK!");
    }else{
      response->success = false;
      response->money = request->money;
      RCLCPP_INFO(this->get_logger(), "NO!");
    }
    RCLCPP_INFO(this->get_logger(), "get a service that request\n success is %d \n money is %d", response->success, response->money);
  }

  // 服务端
  rclcpp::Service<tutorial_interfaces::srv::Money>::SharedPtr money_service;

  // 回调组
  rclcpp::CallbackGroup::SharedPtr money_service_callbackgroup;

};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<MinimalServicer>();
  rclcpp::spin(std::make_shared<MinimalServicer>());
  rclcpp::shutdown();
  return 0;
}