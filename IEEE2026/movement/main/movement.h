//
// Created by Nathan Jones on 10/9/25.
//

#ifndef IEEE2026_MOVEMENT_H
#define IEEE2026_MOVEMENT_H
class Movement {
    public:
        void activateMotors();
        void deactivateMotors();
        void moveForward();
        void moveBackward();
        void turnLeft();
        void turnRight();
        void strafeLeft();
        void strafeRight();
        void stopMovement();
};

#endif //IEEE2026_MOVEMENT_H
