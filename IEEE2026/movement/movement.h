//
// Created by Nathan Jones on 10/9/25.
//

#ifndef IEEE2026_MOVEMENT_H
#define IEEE2026_MOVEMENT_H

class Movement {
public:
    enum Direction { FORWARD, BACKWARD, STOP };
private:
    static void rotateFront(Direction direction);
    static void rotateBack(Direction direction);
    static void rotateA(Direction direction);
    static void rotateB(Direction direction);
public:
    static void moveForward();
    static void moveBackward();
    static void turnLeft();
    static void turnRight();
    static void strafeLeft();
    static void strafeRight();
    static void stopMovement();

};

#endif //IEEE2026_MOVEMENT_H
