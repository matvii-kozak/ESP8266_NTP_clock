# ESP8266_NTP_clock
Simple NTP clock on ESP8266, with a seven-segment display
Hi everyone, I built a clock on ESP8266 that fetches accurate time from an NTP server and displays it on a custom large seven-segment display.
I do firmware in  Arduino IDE, esp8266 connecting to ntp server by wifi so you need to enter your ssdi and password & set time offset in seconds ( 1 hour 3600seconds). 
In the project, I added a PCB if you need it and a schematic. On the PCB, there are 4 drivers, ULN2003 and 74hc595 shift register chips. Also, on the PCB, you can find a switch for summer time if necessary. 
I made the diy seven-segment display by wood cut on a laser machine, or you can cut it by your hands. As LEDs I put the LED stripe in a slot which was cut. As a display, I useda  piece of white plastic. I added drawing file in vector graphics.
