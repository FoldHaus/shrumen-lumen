var ws281x = require('rpi-ws281x-native');

class PadInterface {
	constructor(numLEDs) {
		this.state = 'off'
		this.numLEDs = numLEDs;
		this.brightness = 128;
		this.pixelData = new Uint32Array(numLEDs);

		
		ws281x.init(NUM_LEDS);
	}

	static color(r, g, b){
		r = r * brightness / 255;
		g = g * brightness / 255;
		b = b * brightness / 255;
		return ((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF);
	}

	green() {
		if(this.state == 'green') {
			this.state = 'green';
			var pixelData = this.pixelData;
			for(var i = 0; i < this.numLEDs; i++){
				pixelData[i] = PadInterface.color(0, 255, 0); 
			}
			ws281x.render(pixelData);
			this.pixelData = pixelData;
		}
	}

	red() {
		if(this.state == 'red') {
			this.state = 'red';
			var pixelData = this.pixelData;
			for(var i = 0; i < this.numLEDs; i++){
				pixelData[i] = PadInterface.color(255, 0, 0); 
			}
			ws281x.render(pixelData);
			this.pixelData = pixelData;
		}
	}

	wheel(pos) {
		pos = 255 - pos;
		if(pos < 85) { return PadInterface.color(255 - pos * 3, 0, pos * 3); }
		else if(pos < 170) { pos -= 85; return PadInterface.color(0, pos * 3, 255 - pos * 3); }
		else {
			pos -= 170;
			return PadInterface.color(pos * 3, 255 - pos * 3, 0);
		}
	}

	lightsOff() {
		for(var i = 0; i < NUM_LEDS; i++){
			pixelData[i] = PadInterface.color(0, 0, 0); 
		}
		ws281x.render(pixelData);
		ws281x.reset();
	}
}


module.exports = PadInterface;