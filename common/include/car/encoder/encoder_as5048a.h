#ifndef CAR_ENCODER_AS5048AH
#define CAR_ENCODER_AS5048AH

#include <cstdint>
#include <car/encoder/encoder.h>

namespace car {
namespace encoder {
class AS5048A : public Encoder {
    public:
        AS5048A();
        
        /**
        * Inits SPI peripheral. This function has to be called before any SPI communication
        * @param SPI_CLK - The SPI Clock Pin
        */
        void init(uint8_t SPI_CLK);

        /**
         * Raw SPI transfer. Sends the predefined bit combination (refer to AMS sensor data sheet for more details)
         * and get the response. The response is 14 bits long so some bitwise operations are performed to get the actual value.
         * @param SPI_CS - Motor object
         * @return - 14 bit rotary encoder position
         */
        uint16_t get_raw(uint8_t SPI_CS);
};
}
}
#endif // CAR_ENCODER_AS5048AH
