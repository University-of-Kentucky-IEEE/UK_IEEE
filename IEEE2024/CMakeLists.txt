cmake_minimum_required(VERSION 3.29)
project(IEEE2024)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(IEEE2024
        Functions.ino
        Global_Int.h
        IEEERobot2024.ino
        MovementFunctions.ino
        Pixy2_Functions.ino
        Robotic_Arm_Functions.ino
        SensorFunctions.ino
        Functions.ino
        Functions.ino
        SensorFunctions.ino
        IEEERobot2024/IEEERobot2024.ino)
