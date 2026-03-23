# SoutheasternCon 2026 Competition Code

The `SEC` directory holds production-ready code and assets deployed during the 2026 SoutheasternCon (SEC) competition run on the JetAcker 2WD robot platform (HiWonder JetAcker running on NVIDIA Jetson Orin Nano).

---

## Directory Structure

```
SEC/
├── SEC_2026_Code/
│   └── ackermann_controller.py   # Competition run script for the JetAcker robot
└── vision/
    └── DeepStream-Yolo/          # GPU-accelerated object detection via NVIDIA DeepStream
        ├── duck_tracker/         # Rubber duck detection models and configs (competition task)
        ├── nvdsinfer_custom_impl_Yolo/  # Custom TensorRT/DeepStream YOLO inference plugin
        ├── *.onnx / *.engine     # Exported ONNX and compiled TensorRT engine files
        └── config_infer_primary_*.txt   # DeepStream inference config files per model family
```

---

## SEC_2026_Code

**`SEC_2026_Code/ackermann_controller.py`** is the primary competition run script.

It coordinates the JetAcker 2WD robot's two subsystems:

| Subsystem | Interface | Purpose |
|-----------|-----------|---------|
| Rear drive motors | `/dev/ttyACM0` (serial) via `MotorController` | Forward/reverse drive in RPS |
| Front steering servo | `/dev/rrc` via HiWonder Board SDK | Ackermann steering, servo positions 0–1000 (500 = center) |

The script encodes a timed dead-reckoning sequence for the two competition tasks (button pressing and rubber duck pushing), with configurable motor speeds and steering positions. It is standalone and does not require a running ROS instance.

**To run:**
```bash
python3 /mnt/nova_ssd/workspaces/isaac_ros-dev/src/main/UK_IEEE/IEEE2026/SEC/SEC_2026_Code/ackermann_controller.py
```

**To set steering to a specific position and exit (useful for calibration):**
```bash
python3 ackermann_controller.py --steer-position 500
```

Dependencies resolved at runtime from:
- `MotorController` — from `src/MotorControllerBoard/`
- `ros_robot_controller_sdk.Board` — from `src/HiWonder_Software/cadeJetson/ros2_ws/src/driver/ros_robot_controller/ros_robot_controller/`

---

## vision

**`vision/DeepStream-Yolo/`** contains the GPU-accelerated object detection pipeline used to detect rubber ducks during the SEC competition.

### Key Contents

| Path | Purpose |
|------|---------|
| `duck_tracker/` | Competition-specific duck detection: ONNX models, TensorRT engines, DeepStream configs |
| `duck_tracker/rubber_duck_fixed.onnx` | Primary duck detection model (fixed export for TensorRT) |
| `duck_tracker/deepstream_app_config.txt` | DeepStream pipeline config for duck tracking |
| `nvdsinfer_custom_impl_Yolo/` | Custom C++/CUDA DeepStream plugin — parses YOLO bounding box outputs and handles TensorRT layer ops |
| `nvdsinfer_custom_impl_Yolo/libnvdsinfer_custom_impl_Yolo.so` | Compiled shared library (must be rebuilt if DeepStream/TensorRT version changes) |
| `*.engine` | TensorRT engine files compiled for this specific Jetson GPU — not portable across devices |
| `config_infer_primary_*.txt` | Per-model-family DeepStream inference configuration files |

### Running Duck Detection

```bash
deepstream-app -c /mnt/nova_ssd/workspaces/isaac_ros-dev/src/main/UK_IEEE/IEEE2026/SEC/vision/DeepStream-Yolo/duck_tracker/deepstream_app_config.txt
```

> **Note:** The `.engine` files are compiled for the specific Jetson Orin Nano GPU on this machine. If models are updated or the Jetson is replaced, re-export the ONNX and recompile the engine via DeepStream.

---

## Where to Find Everything on the Jetson

All project code lives under `/mnt/nova_ssd/workspaces/isaac_ros-dev/src/`. Below is a map of the relevant directories:

```
/mnt/nova_ssd/workspaces/isaac_ros-dev/src/
├── main/UK_IEEE/IEEE2026/          # UK IEEE team code (this repo)
│   ├── SEC/                        # ← YOU ARE HERE (competition production code)
│   ├── movement/main/              # Arduino firmware for mecanum/movement (main.ino, movement.cpp)
│   ├── testing/                    # Pre-competition integration tests
│   ├── docs/                       # Team documentation
│   └── Libraries/                  # Shared libraries
│
├── MotorControllerBoard/           # Motor controller serial driver (motor_controller.py)
│                                   # Provides MotorController class used by ackermann_controller.py
│
├── HiWonder_Software/              # HiWonder JetAcker platform SDK and ROS2 drivers
│   └── cadeJetson/ros2_ws/src/
│       ├── driver/
│       │   ├── ros_robot_controller/      # Board SDK (ros_robot_controller_sdk) — servo control
│       │   ├── ros_robot_controller_msgs/ # ROS2 message interfaces for board
│       │   ├── controller/                # High-level controller nodes
│       │   └── servo_controller/         # Servo controller ROS2 package
│       ├── navigation/             # Nav2-based navigation configs for JetAcker
│       ├── slam/                   # SLAM launch files
│       └── bringup/                # Robot bringup launch files
│
├── EdgeAIJetson/                   # Additional competition tools
│   ├── Movement/                   # Standalone Python drive/steer test scripts
│   │   ├── ackermann_controller.py # Development version (promoted copy lives in SEC_2026_Code/)
│   │   ├── motor_controller.py
│   │   └── boot_gpio_trigger.py    # GPIO-based run trigger (physical start button)
│   └── duck_chaser.py              # Experimental vision-to-drive integration script
│
├── SEC2026/                        # ROS2 navigation and SLAM packages for SEC
│   ├── sec2026_nav/                # Nav2 configuration and launch files
│   └── sec2026_slam/               # SLAM configuration and launch files
│
├── Isaac_ROS_Folder/               # NVIDIA Isaac ROS packages
│   ├── isaac_ros_common/           # Shared utilities, Docker, launch helpers
│   └── isaac_ros_visual_slam/      # GPU-accelerated Visual SLAM (cuVSLAM)
│
├── third_party_ros2/               # Third-party ROS2 packages (colcon workspace)
│   ├── third_party_ws/src/
│   │   ├── sllidar_ros2/           # Slamtec RPLIDAR A/S/C series ROS2 driver
│   │   ├── ydlidar_ros2_driver/    # YDLidar ROS2 driver
│   │   ├── ldlidar_stl_ros2/       # LDROBOT LiDAR ROS2 driver
│   │   ├── apriltag_ros/           # AprilTag detection ROS2 node
│   │   ├── apriltag_msgs/          # AprilTag ROS2 message types
│   │   ├── rf2o_laser_odometry/    # Laser odometry from 2D LiDAR scans
│   │   ├── teb_local_planner/      # Time Elastic Band local planner (Nav2)
│   │   ├── costmap_converter/      # Costmap polygon conversion for TEB
│   │   ├── imu_calib/              # IMU calibration node
│   │   ├── laser_filters/          # Laser scan filter nodes
│   │   └── web_video_server/       # HTTP video streaming from ROS image topics
│   ├── orbbec_ws/src/
│   │   └── OrbbecSDK_ROS2/         # Orbbec depth camera (Astra/Gemini) ROS2 driver
│   ├── YDLidar-SDK/                # YDLidar C++ SDK (dependency for ydlidar_ros2_driver)
│   └── Open3D/                     # Open3D library (3D point cloud processing)
│
└── RTAPMAP/                        # RTAB-Map SLAM
    ├── rtabmap/                    # RTAB-Map C++ library source
    └── rtabmap_ws/src/             # RTAB-Map ROS2 wrapper packages
```

---

## How It All Comes Together

The competition stack layers hardware drivers, perception, and autonomous control as follows:

```
┌──────────────────────────────────────────────────────────────────────┐
│                     Competition Run                                   │
│           SEC_2026_Code/ackermann_controller.py                       │
│  (timed dead-reckoning: drive + steer sequences for each task)        │
└────────────────────┬────────────────────┬────────────────────────────┘
                     │                    │
          ┌──────────▼──────┐   ┌─────────▼──────────────┐
          │  MotorController │   │   HiWonder Board SDK    │
          │  (serial/USB     │   │   ros_robot_controller  │
          │   /dev/ttyACM0)  │   │   _sdk — /dev/rrc       │
          │  Rear drive      │   │   Front steering servo  │
          └──────────────────┘   └────────────────────────┘

┌──────────────────────────────────────────────────────────────────────┐
│                    Vision Pipeline (DeepStream)                       │
│         vision/DeepStream-Yolo/duck_tracker/                         │
│  Camera → DeepStream pipeline → YOLO ONNX → TensorRT engine          │
│  → nvdsinfer_custom_impl_Yolo.so (custom bbox parser)                 │
│  → Bounding box overlay / detection output                            │
└──────────────────────────────────────────────────────────────────────┘

┌──────────────────────────────────────────────────────────────────────┐
│              ROS2 / Navigation Stack (optional / future)              │
│  SEC2026/sec2026_nav  +  SEC2026/sec2026_slam                         │
│  ├── Nav2 (navigation2) — autonomous path planning                   │
│  ├── RTAB-Map (RTAPMAP/) — 3D SLAM from depth + LiDAR                │
│  ├── Isaac ROS Visual SLAM (Isaac_ROS_Folder/) — GPU cuVSLAM         │
│  ├── Orbbec depth camera (third_party_ros2/orbbec_ws/)               │
│  ├── LiDAR drivers: sllidar / ydlidar / ldlidar                      │
│  ├── AprilTag detection (apriltag_ros)                                │
│  └── TEB local planner (teb_local_planner)                           │
└──────────────────────────────────────────────────────────────────────┘

┌──────────────────────────────────────────────────────────────────────┐
│                   NVIDIA Jetson Orin Nano                             │
│  JetPack + CUDA + TensorRT + DeepStream + ROS2 Humble                │
└──────────────────────────────────────────────────────────────────────┘
```

**For SEC 2026, the competition run uses only the lower two layers** — the `ackermann_controller.py` dead-reckoning script and the DeepStream duck detection pipeline — running directly on the Jetson without ROS. The full ROS2/Nav2/SLAM stack exists for future autonomous development.

---

## Workflow

1. Develop and test motion sequences in `src/EdgeAIJetson/Movement/` or `src/main/UK_IEEE/IEEE2026/movement/`.
2. Validate via `src/main/UK_IEEE/IEEE2026/testing/`.
3. Promote stable, competition-ready code to `SEC/SEC_2026_Code/`.
4. Train or export updated detection models, then place ONNX files in `vision/DeepStream-Yolo/duck_tracker/` and recompile the TensorRT engine on the Jetson.

## Deployment Checklist

- [ ] Verify robot passes hardware safety inspection and software self-tests.
- [ ] Confirm `/dev/ttyACM0` (motor controller) and `/dev/rrc` (steering board) are present.
- [ ] Run `ackermann_controller.py` in open space to verify tuned timing constants.
- [ ] Confirm TensorRT `.engine` file is up to date (recompile after ONNX changes).
- [ ] Archive released scripts and configs alongside model checkpoints.
- [ ] Document any known issues, last-minute timing changes, and operator notes below.

## Known Issues / Operator Notes

_Record competition-day adjustments, timing tweaks, and anomalies here._
