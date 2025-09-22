# SoutheasternCon Competition Code

The `SEC` directory is reserved for production-ready code and assets that will be deployed during the 2026 SoutheasternCon competition run.

## Scope
- Stable firmware releases for the competition robot.
- Configuration files, calibration values, and mission scripts vetted through full integration testing.
- Documentation of deployment procedures and emergency rollback plans.

## Workflow Expectations
1. Develop features in subsystem folders (e.g., `../movement`) and validate them via `../testing` before promoting them here.
2. Use semantic versioning or tagged releases to track competition builds.
3. Record known issues, TODOs, and operator notes in this README or linked documents.

## Deployment Checklist
- Verify the robot passes hardware safety inspections and software self-tests.
- Confirm all dependencies, toolchains, and flashing procedures are documented.
- Archive released binaries and configuration snapshots alongside the source code.
