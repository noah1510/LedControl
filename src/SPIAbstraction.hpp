/**
 * @file SPIAbstraction.hpp
 * @author Noa Sakurajin (noasakurajin@web.de)
 * @brief This file provides an Abstration for SPI calls
 * @version 0.1
 * @date 2021-05-30
 * @warning This is not a simple replacement for the Arduino SPI.h,
 * but instead implements its own interface.
 * 
 * @copyright Copyright (c) 2021
 * 
 * @details This is a generic SPI interface that can compile for every
 * platform supported by ArduinoAbstraction.hpp. The implementation of
 * this generic interface is handled by the SPIAbstraction.cpp file and
 * this header is the platform independend Interface.
 * 
 */

#pragma once

#include "ArdiunoAbstraction.hpp"

#include <SPI.h>
