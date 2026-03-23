# IEEE 2026 Robotics Team

> Repository for the University of Kentucky IEEE Student Branch SoutheastCon 2026 robotics project.

## Quick Links
- [Team Notion Workspace](https://uky-ieee-student-branch.notion.site/University-of-Kentucky-IEEE-230e04d3af04805ca183c6dcd95bffa5?pvs=74)
- [IEEE BBNvolved](https://uky.campuslabs.com/engage/organization/ieee)

---

## Table of Contents
1. [Overview](#overview)
2. [Season Goals](#season-goals)
3. [Robot Platform](#robot-platform)
4. [Project Structure](#project-structure)
5. [Jetson Workspace Layout](#jetson-workspace-layout)
6. [Getting Started](#getting-started)
7. [Development Workflow](#development-workflow)
8. [Documentation Standards](#documentation-standards)
9. [Resources](#resources)

---

## Overview

The SoutheasternCon robotics competition challenges teams to design, build, and program an autonomous system to accomplish a series of tasks within a constrained field. This repository houses the software, hardware design files, and supporting documentation for the University of Kentucky IEEE Student Branch 2025–26 competitive season.

The competition robot for 2026 is a **HiWonder JetAcker 2WD** — an Ackermann-steering platform running on an **NVIDIA Jetson Orin Nano**, combining rear-wheel drive motors with a front steering servo. Competition tasks include button pressing and rubber duck pushing, executed via a timed dead-reckoning script and GPU-accelerated duck detection.

---

## Season Goals

- Deliver a reliable robot platform capable of meeting the 2026 game manual field requirements.
- Develop modular software for drive control, steering, and vision-based object detection.
- Stand up a testing strategy covering bench verification and on-field validation.
- Maintain documentation so future teams can build on what we learn this season.

---

## Robot Platform

| Component | Details |
|-----------|---------|
| Base | HiWonder JetAcker 2WD (Ackermann steering) |
| Compute | NVIDIA Jetson Orin Nano |
| Drive | Rear brushed DC motors via motor controller board (`/dev/ttyACM0`) |
| Steering | Front servo via HiWonder ROS Robot Controller board (`/dev/rrc`) |
| Vision | Camera + NVIDIA DeepStream + YOLOv11 / custom rubber duck ONNX model |
| LiDAR | YDLidar / Slamtec RPLIDAR (available for future navigation) |
| Depth Camera | Orbbec (available for future SLAM) |

---

## Project Structure

```
IEEE2026/
├── SEC/                    # Competition production code (deploy from here)
│   ├── SEC_2026_Code/      # ackermann_controller.py — competition run script
│   └── vision/             # DeepStream-YOLO duck detection pipeline
│       └── DeepStream-Yolo/
│           └── duck_tracker/   # Competition duck detection models & configs
├── movement/               # Arduino firmware for mecanum/drive testing
│   └── main/               # main.ino — F/B/L/R/strafe movement sequences
├── juniorTeam/             # Junior team tank-drive firmware
│   └── moveTank/           # moveTank.ino
├── testing/                # Integration tests, bench test scripts, validation
├── docs/                   # Design documents, wiring diagrams, datasheets
├── examples/               # Reference sketches (Arduino blink, etc.)
└── Libraries/              # Shared code libraries
```

See each subdirectory's own `README.md` for details.

### Key Files

| File | Purpose |
|------|---------|
| `SEC/SEC_2026_Code/ackermann_controller.py` | **Primary competition run script.** Executes timed drive+steer sequences for all competition tasks. |
| `SEC/vision/DeepStream-Yolo/duck_tracker/` | Duck detection models (ONNX/TensorRT engine) and DeepStream pipeline configs. |
| `movement/main/main.ino` | Arduino mecanum drive test sketch (F, B, L, R, strafe L/R). |
| `juniorTeam/moveTank/moveTank.ino` | Junior team tank-drive Arduino sketch. |

---

## Jetson Workspace Layout

All team and dependency code lives on the Jetson under `/mnt/nova_ssd/workspaces/isaac_ros-dev/src/`. The table below shows how each folder relates to this repository:

```
/mnt/nova_ssd/workspaces/isaac_ros-dev/src/
│
├── main/UK_IEEE/IEEE2026/              ← THIS REPO (cloned here on the Jetson)
│   ├── SEC/                            Production competition code
│   ├── movement/                       Arduino drive firmware
│   ├── testing/                        Validation scripts
│   └── ...
│
├── MotorControllerBoard/               Serial driver for rear drive motors
│                                       Provides motor_controller.py (MotorController class)
│
├── HiWonder_Software/                  HiWonder JetAcker platform SDK + ROS2 packages
│   └── cadeJetson/ros2_ws/src/
│       ├── driver/ros_robot_controller/    Board SDK (steering servo control)
│       ├── driver/ros_robot_controller_msgs/
│       ├── navigation/                     Nav2 configs for JetAcker
│       └── slam/                           SLAM launch files
│
├── EdgeAIJetson/                       Additional scripts used during development
│   ├── Movement/                       Standalone Python motor/steer test scripts
│   └── duck_chaser.py                  Experimental vision-to-drive integration
│
├── SEC2026/                            ROS2 Nav2 + SLAM packages for competition
│   ├── sec2026_nav/                    Nav2 launch + config
│   └── sec2026_slam/                   SLAM launch + config
│
├── Isaac_ROS_Folder/                   NVIDIA Isaac ROS (GPU-accelerated)
│   ├── isaac_ros_common/               Shared utilities and Docker configs
│   └── isaac_ros_visual_slam/          cuVSLAM — visual SLAM on the GPU
│
├── third_party_ros2/                   Third-party ROS2 package collection
│   ├── third_party_ws/src/
│   │   ├── sllidar_ros2/               Slamtec RPLIDAR driver
│   │   ├── ydlidar_ros2_driver/        YDLidar driver
│   │   ├── apriltag_ros/               AprilTag detection
│   │   ├── rf2o_laser_odometry/        2D LiDAR odometry
│   │   ├── teb_local_planner/          TEB local planner (Nav2)
│   │   └── web_video_server/           HTTP video stream from ROS topics
│   └── orbbec_ws/src/OrbbecSDK_ROS2/  Orbbec depth camera driver
│
└── RTAPMAP/                            RTAB-Map 3D SLAM
    ├── rtabmap/                        RTAB-Map C++ library source
    └── rtabmap_ws/src/                 RTAB-Map ROS2 wrapper packages
```

For the full breakdown of how these pieces connect at runtime, see [`SEC/README.md`](SEC/README.md).

---

## Getting Started

1. **Clone the repository**
   ```bash
   git clone https://github.com/University-of-Kentucky-IEEE/UK_IEEE.git
   git submodule update --init --recursive
   cd UK_IEEE/IEEE2026
   ```

2. **On the Jetson** — the workspace is already cloned at:
   ```
   /mnt/nova_ssd/workspaces/isaac_ros-dev/src/main/UK_IEEE/IEEE2026/
   ```

3. **Review onboarding in Notion** — equipment check-out procedures, coding standards, and season milestones are in the Notion workspace.

4. **Set up your development environment**
   - Install VS Code with PlatformIO and GitLens extensions.
   - For Arduino firmware (`movement/`, `juniorTeam/`): use PlatformIO or the Arduino IDE.
   - For Python scripts (`SEC/SEC_2026_Code/`): Python 3.10 on the Jetson, no additional install needed.
   - For ROS2 packages: source the workspace with `source /mnt/nova_ssd/workspaces/isaac_ros-dev/install/setup.bash`.

5. **Sync with the team** — join communication channels, attend weekly project meetings, and check the sprint backlog.

> Keep firmware, CAD, and documentation files under version control. Large binaries (model weights, CAD exports) should be stored via the cloud storage links in Notion.

---

## Development Workflow

- **Branching:** Create feature branches from `main` using descriptive names (e.g., `feature/drive-controller`, `bugfix/steering-calibration`).
- **Commits:** Write clear commit messages explaining the "why." Reference Notion tasks or GitHub issues when possible.
- **Pull Requests:** Open a PR once your feature is ready for review. Include testing notes, screenshots, and any remaining TODOs. Request a review from the relevant subsystem lead.
- **Promoting to SEC:** Develop and validate in `movement/` or `EdgeAIJetson/Movement/`, then promote stable competition-ready code to `SEC/SEC_2026_Code/`.
- **Code Reviews:** Use the review checklist in Notion to verify coding style, documentation, and testing coverage before merging.

---

## Documentation Standards

- Update this README whenever the repository structure or onboarding steps change.
- Each subdirectory must have its own `README.md` describing its contents and how to build/run.
- Keep subsystem-specific documentation in `docs/` or linked in Notion.
- Log major design decisions, test results, and lessons learned in the team's Notion engineering journal.
- Use diagrams (block diagrams, wiring diagrams, flowcharts) to clarify complex systems. Store source files alongside exported images.

---

## Resources

- [SoutheasternCon Robotics Competition](https://site.ieee.org/southeastcon/robotics/) – official rules, updates, and scoring rubric.
- [PlatformIO Documentation](https://docs.platformio.org/) – embedded development environment for Arduino firmware.
- [Arduino Reference](https://www.arduino.cc/reference/en/) – library and API reference.
- [ROS 2 Humble Tutorials](https://docs.ros.org/en/humble/Tutorials.html) – used for navigation and SLAM stack.
- [NVIDIA DeepStream SDK](https://developer.nvidia.com/deepstream-sdk) – used for GPU-accelerated duck detection pipeline.
- [NVIDIA Isaac ROS](https://github.com/NVIDIA-ISAAC-ROS) – GPU-accelerated ROS2 packages (Visual SLAM, image processing).
- [HiWonder JetAcker Documentation](https://www.hiwonder.com) – robot platform hardware and SDK docs.
