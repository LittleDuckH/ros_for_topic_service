cmake_minimum_required(VERSION 3.8)
project(ros_pub_sub)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tutorial_interfaces REQUIRED)  

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

add_executable(pub_node src/pub.cpp)
ament_target_dependencies(pub_node rclcpp tutorial_interfaces)

add_executable(sub_node src/sub.cpp)
ament_target_dependencies(sub_node rclcpp tutorial_interfaces)

install(TARGETS
  pub_node
  sub_node
  DESTINATION lib/${PROJECT_NAME}

)

ament_package()
