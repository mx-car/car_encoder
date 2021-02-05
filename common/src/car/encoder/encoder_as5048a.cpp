
#include <cstdlib>
#include <cstring>


#include <Arduino.h>
#include <SPI.h>
#include <car/encoder/encoder_as5048a.h>

using namespace car::encoder;

AS5048A::AS5048A(const std::array<uint8_t,2> &pinCS, uint8_t pinCLK, uint32_t clock, uint8_t bitOrder, uint8_t dataMode) 
: Encoder(pinCS, pinCLK, clock, bitOrder, dataMode){
    resolution_ = 1 << 14;
    SPI.begin();
    SPI.setSCK(pinCLK_);
    pinMode(pinsCS_[0], OUTPUT);
    pinMode(pinsCS_[1], OUTPUT);
    digitalWriteFast(pinsCS_[0], HIGH);
    digitalWriteFast(pinsCS_[1], HIGH);
    //SPI settings according to sensor datasheet: clock: max. 10MHz | MSB first | SPI Mode 1  | CPOL=0, CPHA= 1
    settings = new SPISettings(clock, bitOrder, dataMode);
}

void AS5048A::read(uint8_t cs, int16_t &value, uint32_t &stamp){

    SPI.beginTransaction(*settings);
    
    //delayMicroseconds(1);
    digitalWriteFast(cs, LOW); //SPI Mode 1 -> information gest sampled with falling endge
    //delayMicroseconds(1);
    stamp = micros();

    value = SPI.transfer16(0xFFFF) & 0x3FFFu;

    digitalWriteFast(cs, HIGH); //SPI Mode 1 -> receive information with rising edge
    //delayMicroseconds(1);

    SPI.endTransaction();
}