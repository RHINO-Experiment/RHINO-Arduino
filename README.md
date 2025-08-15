# rhino-arduino

switches_tempsensor2: Code to control the switches, and to output the temperatures from the sensors to serial. Requires [MAX31865 library](https://github.com/adafruit/Adafruit_MAX31865) and <SPI.h>. Switch command format: "txtyez" e.g "t1t2e4". Temperature reading format: "T1:12.345,T2:12.345".

get_voltage_due: Used for log powermeter, outputs $V_{out}$ to the Due's serial monitor.

switch_thrower: Code used to control the switches. Switch command format: "txtyez" e.g "t1t2e4".

    
