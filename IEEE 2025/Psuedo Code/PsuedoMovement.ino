// PsuedoCode for movement
#include "Basic Movement.h"

void MoveForward() {
    FL.writeMicroseconds(MinPulse);
    BL.writeMicroseconds(MaxPulse);

    FR.writeMicroseconds(MaxPulse);
    BR.writeMicroseconds(MinPulse);
}
// Move forward  | FROM START
// Turn clockwise 90 deg | FACING CAVE
// Move forward | TOWARDS CAVE ENTRANCE
// Stop | AT BACK OF CAVE (IN MIDDLE)
// Turn clockwise 90 deg | FACING TOP RIGHT CORNER OF CAVE
// Move backward | UNTIL HITTING BACK RIGHT CORNER OF CAVE
// Move forward |
// this is a test 2