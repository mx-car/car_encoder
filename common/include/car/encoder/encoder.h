#ifndef CAR_ENCODER_H
#define CAR_ENCODER_H

#include <cstdint>
#include <array>

namespace car
{
    namespace encoder
    {
        template <typename T>
        struct Measurement {
            uint32_t stamp;    /// microsec
            T value;
        };
        /**
        * enum to define channels in the case of multiple encoders using multiple chip select pins
        */
        enum Channel : int
        {
            cs0 = 0,
            cs1 = 1
        };

        /**
        * Class to read angle encoder values
        */
        class Encoder
        {
        public:
            /**
            * Constructor
            * @param pinCLK  spi clock pin
            * @param pinsCS  spi chip select pins defining the channels
            */
            Encoder(uint8_t pinCLK, std::array<uint8_t,2> pinCS)
                : pinCLK_(pinCLK), pinsCS_(pinCS), resolution_(0)
            {
            }

            /**
             * Raw SPI transfer. 
             * @param channel channels @see Encoder::init
             * @see Encoder::resolution() for the resolution
             * @return rotary encoder position
             */
            virtual Measurement<uint16_t> get_raw(Channel channel) = 0;

            /**
             * Angle resolution 
             * for 14 bit = 2^14 = 16384
             * @return - rotary encoder position in raw values
             */
            uint16_t resolution() const
            {
                return resolution_;
            };

            /**
             * encoder reading in -PI to +PI
             * @param channel channels @see Encoder::init
             * @return - rotary encoder position in rad -PI to +PI
             */
            Measurement<float> get(Channel channel)
            {
                Measurement<uint16_t> measurement_raw = get_raw(channel);
                Measurement<float> measurement = {measurement_raw.stamp, M_TWOPI * (float)measurement_raw.value / (float)(resolution_)-M_PI};
                return measurement;
            };

        protected:
            uint8_t pinCLK_;
            std::array<uint8_t, 2> pinsCS_;
            uint16_t resolution_;
        };
    } // namespace encoder
} // namespace car
#endif // CAR_ENCODER_H
