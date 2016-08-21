#!/bin/bash

command_exists() {
	type "$1" &> /dev/null ;
}

echo "Starting setup..."

echo "Installing Processing..."
if command_exists processing; then
	echo "  - Processing already installed."
else
	echo "  - Downloading and installing..."
	curl https://processing.org/download/install-arm.sh | sudo sh
	echo "  - Updating graphics..."
	sudo aptitude remove libgles2-mesa
	echo "  - Processing installed."
fi

echo "Installing PixelPusher library for Processing..."
if [-d /home/pi/sketchbook/libraries/PixelPusher]; then
        echo "  - PixelPusher library already installed."
else
        echo "  - Downloading and installing..."
	mkdir/home/pi/sketchbook/libraries/PixelPusher
        git clone https://github.com/robot-head/PixelPusher-java.git /home/pi/sketchbook/libraries/PixelPusher
        echo "  - PixelPusher library for Processing installed."
fi

echo "Installing GifAnimation library for Processing..."
if [-d /home/pi/sketchbook/libraries/GifAnimation]; then
        echo "  - GifAnimation library already installed."
else
        echo "  - Downloading and installing..."
	mkdir/home/pi/sketchbook/libraries/GifAnimation
        git clone https://github.com/01010101/GifAnimation.git /home/pi/sketchbook/libraries/GifAnimation
        echo "  - GifAnimation library for Processing installed."
fi

echo "Setting up node..."
if command_exists node; then
	echo "  - Node already installed."
else
	echo "  - Downloading and installing node..."
	curl -sL https://deb.nodesource.com/setup_6.x | sudo -E bash -
	sudo apt-get install -y --force-yes nodejs
	echo "  - Done installing node."
fi

if command_exists npm; then
	echo " - NPM installed."
else
	echo " - NPM insallting..."
	sudo apt-get install -y --force-yes npm
	echo " - NPM insallted."
fi

echo "Setting up framebuffer for autostart..."
if command_exists Xvfb; then
	echo "  - Already installed."
else
	echo "  - Installing xvfb..."
	sudo apt-get install -y --force-yes xvfb libxrender1 libxtst6 libxi6
	echo "  - Done installing."
fi

echo "Setting up WiringPi..."
if [ -d ~/wiringPi ]; then
	echo "  - WiringPi already installed."
else
	echo "  - Installing wiringPi..."
	git clone git://git.drogon.net/wiringPi ~/wiringPi
	pushd ~/wiringPi
	git pull origin
	echo "  - Building wiringPi..."
	./build
	popd ~/
	echo "  - WiringPi installed."
fi

echo "Setting up NeoPixel..."
if [ -d ~/neopixel ]; then
	echo "  - NeoPixel already installed."
else
	echo "  - Installing NeoPixel..."
	sudo apt-get update
	sudo apt-get install -y --force-yes build-essential python-dev git scons swig
	echo "  - Getting library..."
	git clone https://github.com/jgarff/rpi_ws281x.git ~/neopixel
	pushd ~/neopixel
	scons
	pushd python
	sudo python setup.py install
	popd
	popd
	echo "  - NeoPixel library installed."
fi

echo "Setting up other NeoPixel library..."
sudo npm install -g node-gyp
git clone --recursive https://github.com/beyondscreen/node-rpi-ws281x-native.git ~/rpi-ws281x
pushd ~/rpi-ws281x
npm install nan
node-gyp rebuild
popd
echo "Set up NeoPixel library."

echo "Installing Libcurl..."
if echo ldconfig -p | grep libcurl.so.4;  then
        echo "  - Libcurl4 already installed."
else
        echo "  - Downloading and installing..."
        sudo apt-get update
	sudo apt-get install -y --force-yes libcurl4-openssl-dev
        echo "  - Libcurl4 installed."
fi

echo "Initializing all services"
sudo bash /home/pi/Desktop/pi-server/startup/start_services.sh




