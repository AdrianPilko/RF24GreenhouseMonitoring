# RF24GreenhouseMonitoring
This is an arduino project to build single node wireless greenhouse monitoring. Its based on RF24 2.4GHz trancievers. We needed a way of making sure the tomatoes got the optimal quantity of water, based on several variable: temperature, humidity, and soil moisture. We had seen the 

Currently supported sensors
===========================
1) Temperature/Humidity Sensor 
2) Moisture Sensor

Future upgrades
===============
1) water butt level sensor
2) sunshine brightness logging (with ultimate being automatic sunshade)
3) Hozelock attached solonoid to control irrigation based on sensor data
4) arduino controlled vent/window opener (currently is a standard passive opener)

Parts (so far)
==============
Arduino Uno x 2
2.4GHz NRF24L01+PA+LNA SMA Wireless Antenna Transceiver module 1100m + regulator boards x2
DHT22 (AM2302) Temperature/Humidity Sensor 
Soil Hygrometer Moisture Sensor
sandwich box to store the transmitter and other parts and ideally be sealed to IP68 or better.

Known Issues
============
1) Some issues with the transmitter strength, many say a 10uF electrolytic cap accross the GND and VCC pins can help. I tried to keep the power level low on the TX and only send every 30seconds
2) Problems with the calibration of the soild moisture sensor, ie no auto calibration
3) Would be good to have some indication of the state locally to the TX'er, such as an oled display
4) Power drain needs to be monitored and minimised, since will run of either a solar panel and or a phone backup battery bank
5) no retry or two way hand shaking, just fire and forget on the TX side. Have seen ranges in testing through 3 or 4 internal house walls from ground level to 1st floor, but with a droppout of approximately 1 in 4 packets. 
