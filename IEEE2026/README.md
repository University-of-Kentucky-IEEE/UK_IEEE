# IEEE 2026 Robotics Team
> Repository for the University of Kentucky IEEE Student Branch SoutheasternCon 2026 robotics project.
## Quick Links
- [Team Notion Workspace](https://uky-ieee-student-branch.notion.site/University-of-Kentucky-IEEE-230e04d3af04805ca183c6dcd95bffa5?pvs=74)
- [IEEE BBNvolved](https://uky.campuslabs.com/engage/organization/ieee)
## Table of Contents
1. [Overview](#overview)
2. [Season Goals](#season-goals)
3. [Getting Started](#getting-started)
4. [Project Structure](#project-structure)
5. [Development Workflow](#development-workflow)
6. [Documentation Standards](#documentation-standards)
7. [Resources](#resources)
## Overview
The SoutheasternCon robotics competition challenges teams to design, build, and
program an autonomous system that can accomplish a series of tasks within a
constrained field. This repository houses the software, hardware design files,
and supporting documentation for the University of Kentucky IEEE Student Branch
2025-26 competitive season.

## Season Goals
- Deliver a reliable base robot platform capable of meeting the field requirements defined by the 2026 game manual.
- Develop modular software for sensing, navigation, manipulation, and competition-specific scoring.
- Stand up a robust testing strategy that includes simulation, bench verification, and on-field validation.
- Maintain documentation so future teams can build on what we learn throughout the season.
## Getting Started
1. **Clone the repository**
   ```bash
   git clone https://github.com/UK-IEEE/UK_IEEE.git
   git submodule update --init --recursive
   cd UK_IEEE/IEEE2026
   ```
2. **Review onboarding in Notion** – the Notion workspace contains equipment check-out procedures, coding standards, and season milestones.
3. **Set up your development environment**
   - Install Visual Studio Code (recommended) with the extensions for PlatformIO and GitLens.
   - Ensure you have PlatformIO Core or the appropriate toolchain for the microcontroller chosen this year (see the Notion "Hardware" page).
   - Follow the Notion "Software Setup" checklist to install dependencies such as Python tools, firmware flashing utilities, or simulation packages.
4. **Sync with the team** – join the communication channels, attend weekly project meetings, and verify the sprint backlog items assigned to you.
> ℹ️ Keep firmware, CAD, and documentation files under version control. Large binaries and prototypes should be stored using the cloud storage links referenced in Notion.
## Project Structure
The 2026 repository will grow throughout the season. Organize new folders as follows so everyone can navigate quickly:
| Directory | Purpose |
|-----------|---------|
| `movement/` | Directory for the robot movement |
| `testing/` | Scripts and assets for desktop testing, ROS nodes, or kinematic models. |
| `SEC/` | Folder for Southeast Con production code |
| `docs/` | Additional documentation |
| `examples/` | Reference sketches and snippets, starting with Arduino examples. |
| `README.md` | Season overview and quick start guide (this file). |
When you create a new area, add a `README.md` inside that directory describing its contents and how to build or run the code.
## Development Workflow
- **Branching:** Create feature branches from `main` using descriptive names (e.g., `feature/drive-controller` or `bugfix/imu-calibration`).
- **Commits:** Write clear commit messages that explain the "why" behind your change. Reference Notion tasks or GitHub issues when possible.
- **Pull Requests:** Open a PR once your feature is ready for review. Include testing notes, screenshots, and any remaining TODOs. Request a review from the relevant subsystem lead.
- **Code Reviews:** Use the review checklist in Notion to verify coding style, documentation, and testing coverage before merging.
- **Continuous Integration:** If we add CI workflows, ensure they are passing before merging. Document any required manual steps (e.g., hardware-in-the-loop tests).
## Documentation Standards
- Update this README whenever the repository structure or onboarding steps change.
- Keep subsystem-specific documentation in the `docs/` folder or linked in Notion.
- Log major design decisions, test results, and lessons learned in the team's engineering journal on Notion.
- Use diagrams (block diagrams, flow charts, wiring diagrams) to clarify complex systems. Store source files alongside exported images.
## Resources
- [SoutheasternCon Robotics Competition](https://site.ieee.org/southeastcon/robotics/) – official rules, updates, and scoring rubric.
- [PlatformIO Documentation](https://docs.platformio.org/) – embedded development environment used by previous seasons.
- [Arduino Reference](https://www.arduino.cc/reference/en/) – useful for quick prototyping and microcontroller library documentation.
- [ROS 2 Tutorials](https://docs.ros.org/en/iron/Tutorials.html) – explore if the team decides to use ROS for higher-level autonomy.
