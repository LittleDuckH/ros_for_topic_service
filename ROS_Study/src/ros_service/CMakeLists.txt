cmake_minimum_required(VERSION 3.8)
project(ros_service)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()



# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tutorial_interfaces REQUIRED)  
find_package(OpenCV REQUIRED)
find_package(cv_bridge REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

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

add_executable(service_node src/service_test.cpp)
ament_target_dependencies(service_node rclcpp tutorial_interfaces cv_bridge)

add_executable(client_node src/client_test.cpp)
ament_target_dependencies(client_node rclcpp tutorial_interfaces cv_bridge)

target_link_libraries(service_node ${OpenCV_LIBS})
target_link_libraries(client_node ${OpenCV_LIBS})

install(TARGETS
  service_node
  client_node
  DESTINATION lib/${PROJECT_NAME}

)

ament_package()
