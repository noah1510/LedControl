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

namespace sakurajin{
    class SPIconfiguration{
        public:
            uint64_t MOSI = 0;
            uint64_t MISO = 0;
            uint64_t SCLK = 0;
            bool useHardwareSPI = true;
            uint64_t transferSpeed = 400000000;

            bool isValid();
            
    };

    class genericSPI{
        private:
            SPIconfiguration config;
            bool _isValid = false;

            bool inTransaction = false;
            uint64_t currentTransactionPin = 0;
        public:
            genericSPI(const SPIconfiguration& _config);
            ~genericSPI();

            void initSSPin(uint64_t pinNum);

            void beginTransaction(uint64_t SSPin);
            void writeByte(byte data);
            void endTransaction();

            bool isValid() const;
            
    };

}
