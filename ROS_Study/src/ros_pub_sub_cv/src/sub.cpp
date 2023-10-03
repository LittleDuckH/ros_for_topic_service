#include <functional>
#include <memory>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/msg/picture.hpp"                                       // CHANGE
#include <iostream>

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber(): Node("minimal_subscriber")
  {
    subscription_ = this->create_subscription<tutorial_interfaces::msg::Picture>("topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));   // CHANGE
  }

private:
  void topic_callback(const tutorial_interfaces::msg::Picture & msg) const  // CHANGE
  {
   
    cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg.image, sensor_msgs::image_encodings::BGR8);
    cv::Mat img = cv_ptr->image.clone();
    cv::resize(img, resizedFrame, resizedFrame.size());
    // RCLCPP_INFO_STREAM(this->get_logger(), "I heard: '" << msg.num << "'");     // CHANGE
    RCLCPP_INFO(this->get_logger(), "cols = %d, rows = %d", img.cols , img.rows);
    cv::imshow("video", resizedFrame);
    cv::waitKey(1000);
  }
  rclcpp::Subscription<tutorial_interfaces::msg::Picture>::SharedPtr subscription_;  // CHANGE
  cv::Mat resizedFrame = cv::Mat(640, 1080, CV_8UC3, cv::Scalar(255, 255, 255));  
  // cv::Mat resizedFrame;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}