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

sakurajin::genericSPI::~genericSPI(){
    #if ABSTRATION_PLATFORM == 1
        if (config.useHardwareSPI) {
            SPI.end();
        }
    #endif
}

void sakurajin::genericSPI::initSSPin(uint64_t pinNum){
    pinMode(pinNum,OUTPUT);
    digitalWrite(pinNum,HIGH);
}

void sakurajin::genericSPI::beginTransaction(uint64_t pinNum){
    if(inTransaction){return;};

    currentTransactionPin = pinNum;
    digitalWrite(currentTransactionPin,LOW);

    #if ABSTRATION_PLATFORM == 1
        if (config.useHardwareSPI) {
            SPI.beginTransaction(SPISettings(config.transferSpeed, MSBFIRST, SPI_MODE0));
        }
    #endif

    inTransaction = true;
}

void sakurajin::genericSPI::writeByte(byte data){
    if(!inTransaction){return;};

    if(!config.useHardwareSPI){
        shiftOut(config.MOSI, config.SCLK, MSBFIRST, data);
        return;
    }

    #if ABSTRATION_PLATFORM == 1
        if (config.useHardwareSPI) {
            SPI.transfer(data);
        }
    #endif
}

void sakurajin::genericSPI::endTransaction(){
    if(!inTransaction){return;};

    #if ABSTRATION_PLATFORM == 1
        if (config.useHardwareSPI) {
            SPI.endTransaction();
        }
    #endif

    digitalWrite(currentTransactionPin,HIGH);
    currentTransactionPin = 0;
    inTransaction = false;
}

bool sakurajin::genericSPI::isValid() const{
    return _isValid;
}
