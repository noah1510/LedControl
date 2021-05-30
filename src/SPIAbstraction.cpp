#include "SPIAbstraction.hpp"

#include <SPI.h>

sakurajin::genericSPI::genericSPI(const sakurajin::SPIconfiguration& _conf):config{_conf}{

    pinMode(config.MOSI, OUTPUT);
    pinMode(config.MISO, INPUT);
    pinMode(config.SCLK, OUTPUT);

    #if ABSTRATION_PLATFORM == 1
        if (config.useHardwareSPI) {
            SPI.setBitOrder(MSBFIRST);
            SPI.setDataMode(SPI_MODE0);
            SPI.begin();
        }
    #endif

    _isValid = true;
};

void sakurajin::genericSPI::initSSPin(uint64_t pinNum){
    pinMode(pinNum,OUTPUT);
    digitalWrite(pinNum,HIGH);
}

bool sakurajin::genericSPI::isValid() const{
    return _isValid;
}
