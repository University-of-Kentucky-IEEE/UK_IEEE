cmake_minimum_required(VERSION 3.30)
project(IEEE2025)

set(CMAKE_CXX_STANDARD 20)

# NOTE: much of the mangling done here is to have CLion do proper linting for
# files in the IEEE2026 project. Any source must be compiled on Arduino IDE. It
# is currently on the backburner trying to get a build toolchain for compiling
# and flashing to an UNO R3 without Arduino IDE.
include_directories(IEEE2026/Libraries/ArduinoCore-avr/cores/arduino)
include_directories(IEEE2026/Libraries/Stepper/src)
file(GLOB IEEE2026/movement/**)
add_compile_definitions(__AVR_ATmega8__ HAVE_HWSERIAL0 UBRRH)

add_executable(IEEE2025 main.cpp)
