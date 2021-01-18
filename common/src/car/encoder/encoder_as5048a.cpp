
#include <cstdlib>
#include <cstring>


#include <Arduino.h>
#include <SPI.h>
#include <car/encoder/encoder_as5048a.h>

using namespace car::encoder;

AS5048A::AS5048A() 
: Encoder(){
    resolution_ = 1 << 14;
}

void AS5048A::init(uint8_t SPI_CLK){
    SPI.begin();
    SPI.setSCK(SPI_CLK);
}

uint16_t AS5048A::get_raw(uint8_t SPI_CS){
    //SPI settings according to sensor datasheet: clock: max. 10MHz | MSB first | SPI Mode 1  | CPOL=0, CPHA= 1
    const SPISettings settings(10000000, MSBFIRST, SPI_MODE1);
    SPI.beginTransaction(settings);
    
    delayMicroseconds(1);
    digitalWriteFast(SPI_CS, LOW); //SPI Mode 1 -> information gest sampled with falling endge
    //delayMicroseconds(1);

    uint16_t rotaryEncoderValue0 = SPI.transfer16(0xFFFF) & 0x3FFFu;
    //delayMicroseconds(1);

    //command bit15 = 1 (parity) | bit14 = 1 (read) | adresss 0x000 -> B11000000 00000000 = 0xC0000;
    digitalWriteFast(SPI_CS, HIGH); //SPI Mode 1 -> receive information with rising edge
    //delayMicroseconds(1);

    digitalWriteFast(SPI_CS, LOW); //SPI Mode 1 -> information gest sampled with falling endge
    //delayMicroseconds(1);

    rotaryEncoderValue0 = SPI.transfer16(0xFFFF) & 0x3FFFu;
    //delayMicroseconds(1);

    digitalWriteFast(SPI_CS, HIGH); //SPI Mode 1 -> receive information with rising edge
    //delayMicroseconds(1);

    SPI.endTransaction();

    return rotaryEncoderValue0;
}