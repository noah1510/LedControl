/**
 * @file ArdiunoAbstraction.hpp
 * @author Noa Sakurajin (noasakurajin@web.de)
 * @brief An abstraction for Arduino.hpp
 * @version 0.1
 * @date 2021-05-30
 * 
 * @copyright Copyright (c) 2021
 * 
 * @details
 *  This header provides implementation for the arduino platform.
 *  It should provide everything you expect from an Arduino.h header
 *  but is independent of the development board.
 *  This header also defines a variable called ABSTRATION_PLATFORM, which allows
 *  for platform specific implementations.
 * 
 *  The following platforms are supported at the moment:
 *  0 or ndef -> not a supported platform
 *  1 -> Arduino (use the real Arduino.h)
 *  2 -> RaspberryPI (based on wiringPi)
 * 
 *  100 -> ArduinoFake (use this for unit testing)
 * 
 * @warning This is not a portable header file and works differently for
 *  each development board. Make sure not to link against the wrong board.
 *  
 */

#pragma once

#if __has_include("Arduino.h")
    #define ABSTRATION_PLATFORM 1

    #include <Arduino.h>
#elif __has_include("ArduinoFake.h")
    #define ABSTRATION_PLATFORM 100

    #include "ArduinoFake.h"
#else
    #error "No support platform was found! You might want to implement a new one or change the compile target!"

#endif
