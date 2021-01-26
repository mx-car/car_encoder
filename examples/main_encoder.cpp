/*
  ENCODER
  @author Markus Bader
 */

#include <Arduino.h>

#include <car/encoder/encoder_as5048a.h>

uint8_t SPI_SCK = 13;
uint8_t SPI_CS0 = 2;
uint8_t SPI_CS1 = 14;

car::encoder::Encoder *encoder;
car::encoder::Measurement<uint16_t> measurement;
int loop_count = 0;

// the setup routine runs once when you press reset:
void setup()
{
  // initialize the digital pin as an output.
  encoder = new car::encoder::AS5048A(SPI_SCK, std::array<uint8_t, 2>({SPI_CS0, SPI_CS1}));

  Serial.begin(115200); /// init serial
  while (!Serial)
    ;
  Serial.println("Encoder \n");
}

// the loop routine runs over and over again forever:
void loop()
{
  Serial.print(loop_count);
  measurement = encoder->get_raw(car::encoder::cs0);
  Serial.print(" value: ");
  Serial.print(measurement.value);
  Serial.print(", ");
  Serial.print(measurement.stamp);
  Serial.print(" = ");
  Serial.println(encoder->get(car::encoder::cs0).value);
  delay(1000); // wait for a second
  loop_count++;
}