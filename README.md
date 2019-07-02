# Physical computing LED lighting tutorial - LED luminaire with joystick colour temperature control

Driving two high-CRI COB LEDs and dimming/mixing their different CCTs with a joystick interface

### Result

![](Assets/5a%20result.jpg)

### Schematic

![](Assets/5a%20schematic.png)

### Joystick PWM value matrix (useful for coding)

![](Assets/5aJoystick%20PWM%20value%20matrix.png)

### BOM

<pre>
€ 14,00 Adafruit Metro Mini 328 5V 16MHz microcontroller
€ 12,00 2 MEANWELL LDB-500LW CC-PSUs
€  8,00 CITIZEN CLU701-0303C4 (one 2700K, one 4000K)
€  1,00 3M 8810 thermally conductive adhesive tape
€ 14,00 2 fischer elektronik ICK LED R 33 x 16,5 G heat-sinks
€  8,00 Adafruit analog 2-axis thumb joystick w. select button
€  4,00 Half-size transparent breadboard
€  1,00 Jumper cables
€  1,00 2,1mm DC barrel-jack
€  1,00 1µF & 1000 µF 10V el. cap., 2 1kΩ resistors
€ 12,00 MEANWELL GST36E12-P1J PSU
€ 76,00
</pre>  

### Useful links  

μc https://www.adafruit.com/product/2590  
CC-PSU https://www.meanwell.com/Upload/PDF/LDB-L/LDB-L-SPEC.PDF  
LED http://ce.citizen.co.jp/lighting_led/dl_data/datasheet/en/COB_HI_ver2/CLU701-0303C4_0035P_201710.pdf  
Thermally conductive tape https://multimedia.3m.com/mws/media/122119O/3m-thermally-conductive-adhesive-transfer-tapes-8800-series.pdf  
Heat-sink https://www.fischerelektronik.de/web_fischer/de_DE/Kühlkörper/B03.1/Kühlkörper%20für%20LED/PG/ICKLEDR033x16.5G/search.xhtml  
Heat sink calculations https://www.led-heatsink.com/thermal-calculation  
