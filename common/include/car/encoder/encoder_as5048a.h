#ifndef CAR_ENCODER_AS5048AH
#define CAR_ENCODER_AS5048AH

#include <cstdint>
#include <car/encoder/encoder.h>

namespace car {
namespace encoder {
class AS5048A : public Encoder {
    public:
        /**
        * Constructor
        * @param pinCLK  spi clock pin
        * @param pinsCS  spi chip select pins defining the channels
        */
        AS5048A(uint8_t pinCLK, std::array<uint8_t,2> pinCS);
        

        /**
         * Raw SPI transfer. Sends the predefined bit combination (refer to AMS sensor data sheet for more details)
         * and get the response. The response is 14 bits long so some bitwise operations are performed to get the actual value.
         * @param channel channels @see Encoder::init
         * @return - 14 bit rotary encoder position
         */
        Measurement<uint16_t> get_raw(Channel channel);
};
}
}
#endif // CAR_ENCODER_AS5048AH
