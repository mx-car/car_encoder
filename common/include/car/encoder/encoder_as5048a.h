/**
 * @author Markus Bader <markus.bader@mx-robotics.com>
 */

#ifndef CAR_ENCODER_AS5048AH
#define CAR_ENCODER_AS5048AH

#include <cstdint>
#include <car/encoder/encoder.h>
#include <SPI.h>

namespace car {
namespace encoder {
class AS5048A : public Encoder {
    private:
        SPISettings *settings;
    public:
        /**
        * Constructor
        * @param pinCLK  spi clock pin
        * @param pinsCS  spi chip select pins defining the channels
        */
        AS5048A(const std::array<uint8_t,2> &pinCS, uint8_t pinCLK, uint32_t clock = 10000000, uint8_t bitOrder = MSBFIRST, uint8_t dataMode = SPI_MODE1);
        

        /**
         * Raw SPI transfer. Sends the predefined bit combination (refer to AMS sensor data sheet for more details)
         * and get the response. The response is 14 bits long so some bitwise operations are performed to get the actual value.
         * @param channel channels @see Encoder::init
         * @return - 14 bit rotary encoder position
         */
        void read(uint8_t cs, int16_t &value, uint32_t &stamp);

};
}
}
#endif // CAR_ENCODER_AS5048AH
