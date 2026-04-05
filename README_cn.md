[English](./README.md) | 中文版

# ros2Demo

个人学习记录demo, 可做ros2学习参考

a simple ros2Demo, `my_test`是一个没有topic的demo
> - 其实这个仓库就两cpp文件能用, 其他都要通过ros2重新生成
> - 拉代码仓库后把两src备份然后删除src重新生成整个框架
> - 关于自定义数据, cycloneDDS用的idl格式, ros2用的msg文件, 区别是ros2会生成idl文件

---

### 核心逻辑：
**建包 $\rightarrow$ 写代码 $\rightarrow$ 改CMake $\rightarrow$ 补环境 $\rightarrow$ 编译运行**

---

### 1. 环境补全 (仅针对极简镜像)
因为用的是 `ros-core`，必须手动安装编译工具和消息依赖：
```bash
apt update
# 安装编译工具 + 常用构建库 + 示例消息包
apt install -y python3-colcon-common-extensions build-essential cmake ros-$ROS_DISTRO-example-interfaces
```

### 2. 工程搭建
建立工作空间并生成 C++ 包框架：
```bash
mkdir -p /workspace/rosTest/src
cd /workspace/rosTest/src
# 依赖 rclcpp (核心库) 和 example_interfaces (通用消息库)
ros2 pkg create --build-type ament_cmake my_test --dependencies rclcpp example_interfaces
```

### 3. 代码编写 (src目录)
*   **Server.cpp**: 初始化节点 $\rightarrow$ 创建 Service $\rightarrow$ 回调函数里做加法 (`req->a + req->b`)。
*   **Client.cpp**: 初始化节点 $\rightarrow$ 创建 Client $\rightarrow$ `wait_for_service` $\rightarrow$ 发送请求 $\rightarrow$ `spin` 等待结果。

### 4. 编译与运行
回到工作空间根目录 (`/workspace/rosTest`)：

**编译：**
```bash
colcon build
```

**运行 (两个终端)：**
> 必须先 source 环境变量，否则系统找不到你的程序。

```bash
# 终端 1 (Server)
source install/setup.bash
ros2 run my_test my_server

# 终端 2 (Client)
source install/setup.bash
ros2 run my_test my_client
```

