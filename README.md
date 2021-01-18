# car_encoder

Add the following statement to ```platformio.ini``` for testing
```
[env:car_encoder]
platform = teensy
board = teensy31
framework = arduino
monitor_speed = 115200
src_filter = -<main.cpp>  +<../lib/car_encoder/examples/main_encoder.cpp> 
lib_deps =
     SPI     
     # RECOMMENDED
     # Accept new functionality in a backwards compatible manner and patches
     pedvide/Teensy_ADC @ ^8.0.38

     # Accept only backwards compatible bug fixes
     # (any version with the same major and minor versions, and an equal or greater patch version)
     pedvide/Teensy_ADC @ ~8.0.38

     # The exact version
     pedvide/Teensy_ADC @ 8.0.38
```
