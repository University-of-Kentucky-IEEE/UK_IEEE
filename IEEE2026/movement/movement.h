//
// Created by Nathan Jones on 10/9/25.
//

#ifndef IEEE2026_MOVEMENT_H
#define IEEE2026_MOVEMENT_H

class Movement {
public:
    enum Direction { FORWARD, BACKWARD, STOP };

    enum State {
        STOPPED = 0,
        MOVE_FORWARD, MOVE_BACKWARD, MOVE_LEFT, MOVE_RIGHT,
        TURN_LEFT, TURN_RIGHT
    };

private:
    static void rotateFront(Direction direction);
    static void rotateBack(Direction direction);
    static void rotateA(Direction direction);
    static void rotateB(Direction direction);
    
    static State state;

public:
    static void moveForward();
    static void moveBackward();
    static void turnLeft();
    static void turnRight();
    static void strafeLeft();
    static void strafeRight();
    static void stopMovement();

    static inline State getState() { return Movement::state; }
};

#endif //IEEE2026_MOVEMENT_H
