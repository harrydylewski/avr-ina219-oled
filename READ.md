Purpose:

Measures a potentiometer that turns on more neopixels as the voltage increases, the power is measured using a TI INA219 power monitor IC, the result is displayed on an OLED display (SSD1306)

Hardware:

potentiometer on PC0
Neopixel data pin on PB1

I'm using the INA219 dev board and a 128x32 oled display from ebay which 
are both connected to I2C interface on the atmega328p

the F_CPU should be 16MHz
