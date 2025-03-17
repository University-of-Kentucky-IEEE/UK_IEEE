# AprilTag Arduino ESP32 library
AprilTag is a visual fiducial system popular in robotics research. This repository contains an adaption of the original AprilTag 3.0 library to use as an Arduino library for ESP32 boards (ideally ESP32 camera boards).

# Current status
- Tag families: Can detect all tested AprilTag families (eg `16h5`, `25h9`, `36h11`).
- Max distance: to be tested. 5cm, square 36h11 tags can be detected from > 1.5M (might even be further, but haven't tested).
- Processing time per frame: 200ms (2 threads) in SVGA resolution, 150ms (single-thread) in VGA resolution and under 100ms (single-thread) in HVGA resolution, all with pose estimate enabled. `16h5`, `25h9`, and `36h11` families all have about the same processing time under the same conditions.
- Camera resolution: works best with SVGA+ resolution. VGA also works great but might not suitable for small tags. HVGA also works but has limited range.
- Accuracy: No wrong tag detection when using `36h11` family. Sometimes tags might not be detected due to motion blurry or light conditions.
- Memory: 2.5MB used on `pose_estimate.ino` example, with SVGA resolution, `36h11` family, and pose estimation. Might even reduced to just 2MB or 1.5MB when using lower resolution and smaller tag family (eg `16h5`). You can also try ESP32's HIMEM API if you want more memory for your own task.
- Flash size: Only use nearly 500KB of flash in the `pose_estimate.ino` example.

# Features
- All features like you would expect from the original AprilTag library.
- Multithread: The optimal number is 2 threads on 2 ESP32 cores (one per core).
- Debug: Include capture-to-SD feature and conversion script to view the frame and debug later. See example sketches for more info. Other debugging features from original AprilTag library are also kept.
- Fully customizable: You can customize parameters or even library's internal structure to fit your need/RAM.
- This library's aim is for ESP32 (Camera) platform, but it can be used for any other boards in Arduino IDE as long as it has enough RAM.

# How to install?
You can install this library like how you would do with other Arduino libraries on Github: Click on <kbd>Code</kbd> button then click on <kbd>Download ZIP</kbd>. Then open your Arduino IDE, click on <kbd>Sketch</kbd> > <kbd>Include Library</kbd> > <kbd>Add . ZIP Library</kbd>

Two examples sketches are available: `simple_tag_detect` for just tag detection, and `pose_estimate` for tag detection + pose estimation.

# Changes added to original AprilTag library
- Convert structure to Arduino library's
- Change all `double` to `float` (ESP32 only natively support single-precision math)
- Reduce the max number of tags for families like `36h10` and `36h11` to fit ESP32's memory (currently to 35 tags for each of these family). See commit https://github.com/raspiduino/apriltag-esp32/commit/59468385da1e9fff37c0f4e9a8152c1ef546523e for more information. You may modify the number to fit your need, but please check the memory usage.
- Add simple tag detect and pose estimate examples for ESP32-CAM.

# (Old) Development log
See https://github.com/raspiduino/apriltag-esp32/discussions/1

# Credit
- Original [AprilTag](https://github.com/AprilRobotics/apriltag) library developers.
- [gvl610](https://github.com/raspiduino) for the Arduino library version of AprilTag.

# License
BSD 2-Clause License. Same as original AprilTag library.
