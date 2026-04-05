[中文版](./README_cn.md) | English

# ros2Demo

Personal learning demo, can be used as a ROS2 learning reference.

A simple ros2Demo, `my_test` is a demo without topic.
> - Actually, only the two cpp files in this repo are usable; everything else needs to be regenerated via ros2.
> - After cloning the repo, back up the two src files, then delete src and regenerate the entire framework.
> - Regarding custom data: CycloneDDS uses .idl format, while ROS2 uses .msg files. The difference is that ROS2 generates .idl files.

---

### Core Workflow:
**Create package → Write code → Modify CMake → Set up environment → Build and run**

---

### 1. Environment Setup (for minimal images only)
Since `ros-core` is used, build tools and message dependencies must be installed manually:
```bash
apt update
# Install build tools + common build libraries + example message package
apt install -y python3-colcon-common-extensions build-essential cmake ros-$ROS_DISTRO-example-interfaces
```

### 2. Project Setup
Create a workspace and generate the C++ package skeleton:
```bash
mkdir -p /workspace/rosTest/src
cd /workspace/rosTest/src
# Dependencies: rclcpp (core library) and example_interfaces (common message library)
ros2 pkg create --build-type ament_cmake my_test --dependencies rclcpp example_interfaces
```

### 3. Code Writing (src directory)
*   **Server.cpp**: Initialize node → Create Service → Perform addition in callback (`req->a + req->b`).
*   **Client.cpp**: Initialize node → Create Client → `wait_for_service` → Send request → `spin` to wait for result.

### 4. Build and Run
Go back to the workspace root (`/workspace/rosTest`):

**Build:**
```bash
colcon build
```

**Run (two terminals):**
> You must source the environment variables first, otherwise the system won't find your programs.

```bash
# Terminal 1 (Server)
source install/setup.bash
ros2 run my_test my_server

# Terminal 2 (Client)
source install/setup.bash
ros2 run my_test my_client
```

