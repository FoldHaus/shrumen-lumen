var ws281x = require('rpi-ws281x-native');

var NUM_LEDS = parseInt(process.argv[2], 10) || 8,
	pixelData = new Uint32Array(NUM_LEDS);

console.log("Starting with " + NUM_LEDS + " LEDS");

var brightness = 128;

ws281x.init(NUM_LEDS);

var lightsOff = function() {
	for(var i = 0; i < NUM_LEDS; i++){
		pixelData[i] = color(0, 0, 0); 
	}
	ws281x.render(pixelData);
	ws281x.reset();
}

var signals = {
	'SIGINT': 2,
	'SIGTERM': 15
};

function shutdown(signal, value) {
	console.log('Stopped by ' + signal);
	lightsOff();
	process.nextTick(function() { process.exit(0); });
}

Object.keys(signals).forEach(function(signal){
	process.on(signal, function(){
		shutdown(signal, signals[signal]);
	});
});



//-- animation loop

var offset = 0;
setInterval(function() {
	for(var i = 0; i < NUM_LEDS; i++){
		pixelData[i] = wheel(((i * 256 / NUM_LEDS) + offset) % 256);
	}
	offset = (offset + 1) % 256;
	ws281x.render(pixelData);
}, 1000 / 30);

function wheel(pos) {
	pos = 255 - pos;
	if(pos < 85) { return color(255 - pos * 3, 0, pos * 3); }
	else if(pos < 170) { pos -= 85; return color(0, pos * 3, 255 - pos * 3); }
	else {
		pos -= 170;
		return color(pos * 3, 255 - pos * 3, 0);
	}
}


function color(r, g, b){
	r = r * brightness / 255;
	g = g * brightness / 255;
	b = b * brightness / 255;
	return ((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF);
}
