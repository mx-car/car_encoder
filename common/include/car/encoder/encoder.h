#ifndef CAR_ENCODER_H
#define CAR_ENCODER_H

#include <cstdint>

namespace car {
namespace encoder {
class Encoder {
    public:
        Encoder() : resolution_(0) {
        }
        
        /**
        * Inits SPI peripheral. This function has to be called before any SPI communication
        * @param SPI_CLK 
        */
        virtual void init(uint8_t SPI_CLK) = 0;

        /**
         * Raw SPI transfer. 
         * @param SPI_CS - Chip select pin
         * @see Encoder::get_resolution() for the resolution
         * @return - rotary encoder position
         */
        virtual uint16_t get_raw(uint8_t SPI_CS) = 0;

        /**
         * Angle resolution 
         * for 14 bit = 2^14 = 16384
         * @return - rotary encoder position in raw values
         */
        uint16_t resolution() const {
            return resolution_;
        };

        /**
         * encoder reading in -PI to +PI
         * @param SPI_CS - Chip select pin
         * @return - rotary encoder position in rad -PI to +PI
         */
        float get(uint8_t SPI_CS){
           uint16_t v = get_raw(SPI_CS);
           float a = M_TWOPI * (float) v / (float) (resolution_)  - M_PI;
           return a;
        };

    protected:
        uint16_t resolution_;
};
}
}
#endif // CAR_ENCODER_H
