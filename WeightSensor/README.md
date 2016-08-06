# Weight Sensor Application

Using the HX711 sensor board to detect weight using the RPi.

This uses the WiringPi library.

The app will also post the data to http://localhost:3001/sensordata. Use the sample server to view sample output.

Helper files:

+ `sensor1.sh` - Runs application for sensor 1
	+ VCC - pin 4
	+ DAT - pin 10 (GPIO 15)
	+ CLK - pin 12 (GPIO 18)
	+ GND - pin 14

+ `sensor2.sh` - Runs application for sensor 2
	+ VCC - pin 2
	+ DAT - pin 16 (GPIO 23)
	+ CLK - pin 18 (GPIO 24)
	+ GND - pin 20

** NOTE: Pins must be exported to work **

To export a pin, for example GPIO 23:
`echo 23 > /sys/class/gpio/export`

## Sample Server

This folder contains a simple node server in sample server.

Run it using `node sampleserver.js`. This will start a server at http://localhost:3001.

The server has these endpoints:
+ 'GET /' - Root index
+ 'POST /weightsensor' - Will log data to the console

## References

+ [wiringPi](http://andyseasysite.com/?page_id=145)
+ [RPi Pinout](http://docs.biicode.com/raspberrypi/rpi-howto.html#rpigpio)
