# README #

This repository keeps the whole of the Mobile Charger Vending Machine.

### Requirements ###
The machine contains one of coin insert, 4 mobile charger and 4 selects, 4 start/pause and 4 stop/reset button.

* Firstly, select mobile charger by push select button. 
* Secondly, insert coin that the 7 segment shall show the charging time.
* Thirdly, push the start button to start charging that the relay shall be energized, and 7 segments shall show the countdown timer.
* [*Not implemented*] While charging, if start button is pushed, the countdown timer shall pause, and relay shall de-energize.
* While charging, if the stop button is pushed, the countdown timer shall reset to 0, and relay shall de-energize.

### Components ###
* MCU: Arduino Nano
* I/O Expander: MCP23017
* 7 Segment Driver: MAX7219

### Design Description ###
Arduino nano is selected because there is the lowest cost of Arduino. However, the I/O is not enough to provide the many buttons, so I use an I/O expander to solve this problem. The 4 digits 7 segment must be driven by scanning technique. In terms of programming, I have to make forloop for drive it that more CPU usage is taken. MAX7219 is the best solution by using SPI (Serial Peripheral Interface) to communicate with MCU.

### Author 
Sarucha Yanyong