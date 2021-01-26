
#include <cstdlib>
#include <cstring>


#include <Arduino.h>
#include <SPI.h>
#include <car/encoder/encoder_as5048a.h>

using namespace car::encoder;

AS5048A::AS5048A(uint8_t pinCLK, std::array<uint8_t,2> pinCS) 
: Encoder(pinCLK, pinCS){
    resolution_ = 1 << 14;
    SPI.begin();
    SPI.setSCK(pinCLK_);
    pinMode(pinsCS_[0], OUTPUT);
    pinMode(pinsCS_[1], OUTPUT);
    digitalWriteFast(pinsCS_[0], HIGH);
    digitalWriteFast(pinsCS_[1], HIGH);
}

Measurement<uint16_t> AS5048A::get_raw(Channel channel){
    Measurement<uint16_t> measurement;
    uint8_t pinCS = pinsCS_[static_cast<int>(channel)];

    //SPI settings according to sensor datasheet: clock: max. 10MHz | MSB first | SPI Mode 1  | CPOL=0, CPHA= 1
    const SPISettings settings(10000000, MSBFIRST, SPI_MODE1);
    SPI.beginTransaction(settings);
    
    delayMicroseconds(1);
    digitalWriteFast(pinCS, LOW); //SPI Mode 1 -> information gest sampled with falling endge
    //delayMicroseconds(1);
    measurement.stamp = micros();
    measurement.value = SPI.transfer16(0xFFFF) & 0x3FFFu;
    //delayMicroseconds(1);

    //command bit15 = 1 (parity) | bit14 = 1 (read) | adresss 0x000 -> B11000000 00000000 = 0xC0000;
    digitalWriteFast(pinCS, HIGH); //SPI Mode 1 -> receive information with rising edge
    //delayMicroseconds(1);

    digitalWriteFast(pinCS, LOW); //SPI Mode 1 -> information gest sampled with falling endge
    //delayMicroseconds(1);

    measurement.value = SPI.transfer16(0xFFFF) & 0x3FFFu;
    //delayMicroseconds(1);

    digitalWriteFast(pinCS, HIGH); //SPI Mode 1 -> receive information with rising edge
    //delayMicroseconds(1);

    SPI.endTransaction();

    digitalWriteFast(pinsCS_[0], HIGH);
    digitalWriteFast(pinsCS_[1], HIGH);

    return measurement;
}