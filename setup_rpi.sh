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

echo "Setting up node..."
if command_exists node; then
	echo "  - Node already installed."
else
	echo "  - Downloading and installing node..."
	curl -sL https://deb.nodesource.com/setup_6.x | sudo -E bash -
	sudo apt-get install -y nodejs npm
	echo "  - Done installing node."
fi

echo "Setting up framebuffer for autostart..."
if command_exists Xvfb; then
	echo "  - Already installed."
else
	echo "  - Installing xvfb..."
	sudo apt-get install -y xvfb libxrender1 libxtst6 libxi6
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
	sudo apt-get install -y build-essential python-dev git scons swig
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
