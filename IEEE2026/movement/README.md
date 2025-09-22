# Movement Subsystem

This directory will host firmware and control logic for the robot's drive base and motion subsystems.

## Contents
- Motion control algorithms and libraries.
- Interface layers for sensors such as IMUs, wheel encoders, and odometry modules.
- Utilities for tuning PID controllers and motion profiles.

## Getting Started
1. Review the subsystem design notes in the main IEEE 2026 README and the team's Notion space.
2. Create a feature branch for your work (e.g., `feature/drive-profile-generator`).
3. Add source files and update this README with build and deployment steps as the subsystem grows.

## Testing
- Pair movement changes with relevant simulation or bench tests stored in `../testing`.
- Document calibration procedures and expected performance metrics.

## Contributing
- Follow the software standards outlined by the team.
- Keep diagrams, calculations, and notes alongside the code or link to shared documentation in `../docs`.
