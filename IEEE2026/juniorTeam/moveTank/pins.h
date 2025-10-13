//
// Created by Nathan Jones on 10/9/25.
//

#ifndef IEEE2026_PINS_H
#define IEEE2026_PINS_H

// Format for pinout definitions:
// #define ${pin_function} ${pin_number}

#define BUILTIN_LED 13     // temp

// Stepper 1 pins
#define S1_PowerPos 0      // may not be needed
#define S1_PowerNeg 0      // may not be needed
#define S1_SignalPos 0     // 5 or 3.3V
#define S1_SignalNeg 0     // GN
#define S1_SignalAPhase 0  // may not be needed
#define S1_SignalBPhase 0  // may not be needed

// Stepper 2 pins
#define S2_PowerPos 0      // may not be needed
#define S2_PowerNeg 0      // may not be needed
#define S2_SignalPos 0     // 5 or 3.3V
#define S2_SignalNeg 0     // GN
#define S2_SignalAPhase 0  // may not be needed
#define S2_SignalBPhase 0  // may not be needed

#endif //IEEE2026_PINS_H
