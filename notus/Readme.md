Notus
=====

Notus: Sensors data acquisition device

Part of: [Chinook](http://chinook.etsmtl.ca) wind-powered vehicule. 
  
Features
--------

* Input voltage : 7V to 36V
* MCU 		: dsPIC33EP512MC806
* Datalogging 	: SD Card
* RealTimeClock	: DS1338
* EEPROM 	: CAT24C256W
* Accelerometer : MMA8452Q
* DAQ		: MCP4728
* Communication :
  * CANBUS 	: iso1050
  * Serial TTL 	: FT232RL
  * RS232	: MAX3221
  * RS485	: SN65HVD08D

Pins mapping
------------

* SIGNAL_IN0 : INT0/RP64/RD0
* SIGNAL_IN1 : RP65/RD1
* SIGNAL_IN2 : RP66/RD2
* SIGNAL_IN3 : PMBE/RP67/RD3 
* ADC_SENSOR_2 : AN2/C2IN2-/RPI34/RB2
* ADC_SENSOR_3 : AN3/C2IN1+/RPI35/RB3
* ADC_SENSOR_4 : AN4/C1IN2-/RPI36/RB4
* ADC_SENSOR_5 : AN5/C1IN1+/RPI37/RB5

Wind Sensor Pinout (Davis Instruments)
--------------------------------------

* Black : Wind speed contact closure to ground
* Red : Ground 
* Green : Wind direction pot wiper (20KΩ potentiometer)
* Yellow : Pot supply voltage

Known Bugs Hardware REV.0
-------------------------

* Opamp supply are inverted
* EEPROM SDA and SCL are inverted
* RTC xtal won't start 
