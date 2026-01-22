compile:
	avr-gcc -Wall -Werror -mmcu=atmega328p -Os -DF_CPU=16000000UL ledFade.c -o Blink.elf
transform:
	avr-objcopy -O ihex -R .eeprom ledFade.elf ledFade.hex
upload:
	avrdude -p m328p -P /dev/ttyUSB0 -c arduino -U flash:w:ledFade.hex:i -v -b 115200
clear:
	rm ledFade.elf ledFade.hex
edit:
	nvim ledFade.c
