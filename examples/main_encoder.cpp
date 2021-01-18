/*
  ENCODER
  @author Markus Bader
 */

#include <Arduino.h>

#include <car/encoder/encoder_as5048a.h>

int SPI_SCK = 13;
int SPI_CS0 = 2;
int SPI_CS1 = 14;

car::encoder::Encoder *encoder;
int loop_count = 0;

// the setup routine runs once when you press reset:
void setup()
{
  // initialize the digital pin as an output.
  pinMode(SPI_CS0, OUTPUT);
  pinMode(SPI_CS1, OUTPUT);
  encoder = new car::encoder::AS5048A;
  encoder->init(SPI_SCK);
  digitalWriteFast(SPI_CS0, HIGH);
  digitalWriteFast(SPI_CS1, HIGH);

  Serial.begin(115200); /// init serial
  while (!Serial)
    ;
  Serial.println("Encoder \n");
}

// the loop routine runs over and over again forever:
void loop()
{
  Serial.print(loop_count);
  Serial.print(" value: ");
  Serial.print(encoder->get_raw(SPI_CS0));
  Serial.print(", ");
  Serial.println(encoder->get(SPI_CS0));
  delay(1000); // wait for a second
  loop_count++;
}