cmake_minimum_required(VERSION 3.8)
project(my_test)

# 寻找依赖
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)

# 1. 编译 Server
add_executable(my_server src/server.cpp)
ament_target_dependencies(my_server rclcpp example_interfaces)

# 2. 编译 Client
add_executable(my_client src/client.cpp)
ament_target_dependencies(my_client rclcpp example_interfaces)

# 3. 这里是关键：把生成的可执行文件放到 install 目录，让 ros2 run 能找到
# 注意：这只会安装到 /workspace/rosTest/install/my_test/lib/my_test/ 下，不会进系统目录
install(TARGETS
  my_server
  my_client
  DESTINATION lib/${PROJECT_NAME})

ament_package()
