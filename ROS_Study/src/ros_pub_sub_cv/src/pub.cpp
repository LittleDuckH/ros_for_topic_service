#include <chrono>
#include <memory>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/msg/picture.hpp"       
#include <sensor_msgs/image_encodings.hpp>                                     // CHANGE

#include <iostream>

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher(): Node("minimal_publisher")
  {

    // cv::VideoCapture capture("/home/huang/桌面/video_test/video_test_new.mp4");
    // if(!capture.isOpened())
    // {
    //     return -1;
    // }
    // while(capture.read(frame))
    // {
    //   img = frame.clone();
    // }
    img = cv::imread("/home/huang/codes/test.jpg");
    publisher_ = this->create_publisher<tutorial_interfaces::msg::Picture>("topic", 10);  // CHANGE
    timer_ = this->create_wall_timer(500ms, std::bind(&MinimalPublisher::timer_callback, this));
  }



private:
  void timer_callback()
  {
    auto message = tutorial_interfaces::msg::Picture();                                   // CHANGE

    message.image = *cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", this->img).toImageMsg();
    RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: 1");    // CHANGE
    publisher_->publish(message);
  }

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<tutorial_interfaces::msg::Picture>::SharedPtr publisher_;             // CHANGE
  cv::Mat img;

};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}