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
int16_t position0;
uint32_t stamp0;
int16_t position1;
uint32_t stamp1;
int loop_count = 0;

// the setup routine runs once when you press reset:
void setup()
{
  // initialize the digital pin as an output.
  encoder = new car::encoder::AS5048A(std::array<uint8_t, 2>({SPI_CS0, SPI_CS1}), SPI_SCK);

  Serial.begin(115200); /// init serial
  while (!Serial)
    ;
  Serial.println("Encoder \n");
}

// the loop routine runs over and over again forever:
void loop()
{
  Serial.print(loop_count);
  uint32_t start = micros();
  encoder->read(SPI_CS0, position0, stamp0);
  encoder->read(SPI_CS1, position1, stamp1);
  uint32_t stop = micros();
  Serial.print(" motor0: ");
  Serial.print(position0);
  Serial.print(", ");
  Serial.print(stamp0);
  Serial.print("; motor1: ");
  Serial.print(position1);
  Serial.print(", ");
  Serial.print(stamp1);
  Serial.print(", ");
  Serial.println(stop-start);
  delay(1000); // wait for a second
  loop_count++;
}