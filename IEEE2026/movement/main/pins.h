//
// Created by Nathan Jones on 10/9/25.
//

// In reference with https://lastminuteengineers.com/l298n-dc-stepper-driver-arduino-tutorial/

#ifndef IEEE2026_PINS_H
#define IEEE2026_PINS_H

// Motor <Side><Face>
// Sides:
// A - Left
// B - Right
// Faces:
// F - Front
// B - Back

// Directions
// input<Side and direction><Face>
// Sides:
// 1 & 3 - Forward
// 2 & 4 - Backward

// Face:
// F - Front
// B - Back

// Motor AF connections (Front Left)
#define enableAF 9
#define input1F 8 // AF Forward
#define input2F 7 // AF Backward

// Motor BF connections (Front Right)
#define enableBF 3
#define input3F 5 // BF Forward
#define input4F 4 // BF Backward

//Motor AB connections (Back Left)
#define enableAB 19
#define input1B 18 // AB Forward
#define input2B 17 // AB Backward

//Motor BB connections (Back Right)
#define enableBB 14
#define input3B 15 // BB Forward
#define input4B 16 // BB Backward

#endif //IEEE2026_PINS_H
