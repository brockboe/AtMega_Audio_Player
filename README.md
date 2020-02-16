# AtMega_Audio_Player
This code is meant to be run on Atmel AVR's and plays a small audio byte off of a EEPROM chip

The audio is stored as an 8-bit PCM file, which is stored on an EEPROM chip on the PCB. The microcontroller's job is to cycle through the addresses on the EEPROM and feed the 8-bit samples out and into a D2A converter and finally out through a speaker. 

The code in this repository reflects this act, as the address out simply counts up at a specified sampling frequency.
