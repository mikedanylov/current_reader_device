# current_reader_device
Generic power consumption measurement device

####18.07.15 UPDATE. Overall after first proto is made and first firmware for uC
![first proto](misc/proto_1.jpg)
- ACS712 hall sensor is not suitable for high precision current measurements
- 10 bit ADC of 328p 8 bit AVR uC is not enough to get 0.001 mV accuracy

Possible solution might be:
+ use 16 bit external ADC / use another uC with wider ADC
+ try to find another current sensor for lower currents

Since I don't have neither of those devices I currently stop working on this project.


###Introduction
This project is based on my [previous work](https://github.com/mikedanylov/Power_Measurements_Fluke289) where I used Fluke multimeter to measure current consumption of a device. Then I thought that using Fluke 289 for measuring just one parameter most of the time is an overkill considering the price that beasty. Fortunately, I found in my drawer ACS712 chip breakout board [datasheet](http://www.google.fi/url?sa=t&rct=j&q=&esrc=s&source=web&cd=1&ved=0CB8QFjAAahUKEwi6k8aK6tjGAhXBfnIKHTauATA&url=http%3A%2F%2Fwww.allegromicro.com%2F~%2FMedia%2FFiles%2FDatasheets%2FACS712-Datasheet.ashx&ei=vw-kVfq3NcH9yQO23IaAAw&usg=AFQjCNG8Ps3cR0EkgfoM3ZNSpXLpyj7gZg&sig2=GZNgsXu2TxrQYg-yl7z4WA&bvm=bv.97653015,d.bGQ0). Basicaly it is a hall effect current sensor with sensitivity in my package 185mV/A. It is clamed to be rather fast, rated at 80kHz. Therefore, it should be enough for most of the cases of capturing carrent fluctuations. Not sure though how stable and accurate readings I am going to get... But what if? :)

###Draft of operation flow and setup
1. Device is connected to ACS712 hall current sensor
2. Sensor is constantly producing potential difference as its output with sensitivity 185mV/A
3. Output from sensor is connected to 10 bit ADC of ~~attiny85~~ atmega328p microcontroller
4. ~~ADC input is amplified internaly in uC (not sure about this part yet, but [datasheet](http://www.atmel.com/images/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf) of attiny85 claims it is possible)~~
5. Data is transmitted over UART to PC serial port
6. Python script on PC reads serial port and plots a graph

###Limitations
* ADC noise
  + Tried to use oversampling to get 16 bit out of 10bit ADC
* conversion approximation
  + Tried to use different kinds of software filters
* something else will definitely pop up later
  + acs712 sensitivity 185mV/A means that if we want to get 1 mA accuracy we have to read precicely 0.185 mV which is very high accuracy for 10 bit ADC even if we apply oversampling

###Parts
* Atmel AVR ~~attiny85~~ atmega328p microcontroller
* ACS712 breakout board, hall current sensor
* USB to TTL converter module
* 10k resistor, pull-up reset
* 2x100nF capacitors for ADC
* 10 uH inductor for ADC
* 1 push button for reset
* 1 switch for powering on the device
* 1 green LED mostly for debugging
* hookup wires
