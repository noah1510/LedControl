#include "SPIAbstraction.hpp"

#if ABSTRATION_PLATFORM == 1
    #include <SPI.h>
#endif

bool sakurajin::SPIconfiguration::isValid(){
    if (SCLK == 0) {
        return false;
    }

    return true;
}

sakurajin::genericSPI::genericSPI(){};

sakurajin::genericSPI::genericSPI(const sakurajin::SPIconfiguration& _conf):config{_conf}{
    if (config.useHardwareSPI) {
        #if ABSTRATION_PLATFORM == 1
            config.SCLK = SCK;
            config.MOSI = MOSI;
            config.MISO = MISO;
        #endif
    }

    if(!config.isValid()){return;};

    pinMode(config.MOSI, OUTPUT);
    pinMode(config.MISO, INPUT);
    pinMode(config.SCLK, OUTPUT);

    if (config.useHardwareSPI) {
        #if ABSTRATION_PLATFORM == 1    
            SPI.setBitOrder(MSBFIRST);
            SPI.setDataMode(SPI_MODE0);
            SPI.begin();
        #endif
    }

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

void sakurajin::genericSPI::sendByte(byte data){
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
