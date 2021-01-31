#ifndef CAR_ENCODER_H
#define CAR_ENCODER_H

#include <cstdint>
#include <array>

namespace car
{
    namespace encoder
    {

        /**
        * Class to read angle encoder values
        */
        class Encoder
        {
        public:
            /**
            * Constructor
            * @param pinCLK  spi clock pin
            * @param pinCS   spi clock pin
            * @param pinsCS  spi chip select pins defining the channels
            */
            Encoder(const std::array<uint8_t,2> &pinCS, uint8_t pinCLK, uint32_t clock, uint8_t bitOrder, uint8_t dataMode)
                : pinCLK_(pinCLK), pinsCS_(pinCS), resolution_(0)
            {
            }

            /**
             * reads sensor values via SPI  
             * @param cs pin chip select which must match a ping on the pinCS values on the contrustor
             * @param value encode raw values
             * @param stamp time stamp in micro secounds 
             * @see Encoder::resolution() for the resolution
             * @return true on error
             **/
            virtual void read(uint8_t cs, int16_t &value, uint32_t &stamp) = 0;

            /**
             * Angle resolution 
             * for 14 bit = 2^14 = 16384
             * @return - rotary encoder position in raw values
             */
            uint16_t resolution() const
            {
                return resolution_;
            };

        protected:
            uint8_t pinCLK_;
            std::array<uint8_t, 2> pinsCS_;
            uint16_t resolution_;
        };
    } // namespace encoder
} // namespace car
#endif // CAR_ENCODER_H
