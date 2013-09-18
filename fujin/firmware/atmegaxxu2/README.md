Fujin Firmware for the ATmega16u2 (based on [arduino firmware](https://github.com/arduino/Arduino/tree/master/hardware/arduino/firmwares/atmegaxxu2))

To burn:

    avrdude -p m16u2 -F -P usb -c avrispmkii \
            -U flash:w:Arduino-usbserial-atmega16u2-Uno-Rev3.hex \
            -U lfuse:w:0xFF:m -U hfuse:w:0xD9:m -U efuse:w:0xF4:m -U lock:w:0x0F:m
