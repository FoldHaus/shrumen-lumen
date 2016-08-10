var express = require('express');
var bodyParser = require('body-parser');
var engines = require('consolidate');
var mustache = require('mustache');
var Rainbow = require('rainbowvis.js');

var app = express();

app.set('port', (process.env.PORT || 3000));
app.set('views', __dirname + '/public');
app.set('view engine', 'html');
app.engine('html', engines.mustache);
app.use(express.static(__dirname + '/public'));

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
	extended: true
}));

//Add a module containing a class for interacting with the WeightSensor
var WeightSensorInterface = require("./lib/WeightSensorInterface.js");
var weightSensorInterface = new WeightSensorInterface();

//Add a module containing a class for interacting with the WeightSensor
var PadInterface = require("./lib/PadInterface.js");
var padInterface = new PadInterface(60);

// Module for setting state
var setState = require('./lib/setState.js');

var step = 0;

const ledsPerStripCountCap = 90;
const ledsPerStripCountStem = 240;

const ledStripsInCap = 6;
const ledStripsInStem = 2;

const numColorsInRainbow = 400;

var capRainbow = new Rainbow();
capRainbow.setNumberRange(1, numColorsInRainbow);
capRainbow.setSpectrum('blue', 'purple', 'blue');

var stemRainbow = new Rainbow();
stemRainbow.setNumberRange(1, numColorsInRainbow);
stemRainbow.setSpectrum('white', 'white', 'white');

var testStep = 0;
var testColors = [
			['blue', 'green', 'red'], 
			['red', 'yellow', 'blue'],
			['blue', 'orange', 'green'],
			['green', 'white', 'blue']]
			


function getFrame(step) {
	var frame = {
		cap: {},
		stem: {}
	};

	var baseArrayStem = new Array(ledsPerStripCountStem).fill(0);

	for(var i = 0; i < ledStripsInCap; i++) {	
		var baseArrayCap = new Array(ledsPerStripCountCap).fill(capRainbow.colourAt(step));
		frame.cap[i] = baseArrayCap
	}	

	for(var i = 0; i < ledStripsInStem; i++) {	
		var baseArrayStem = new Array(ledsPerStripCountStem).fill(stemRainbow.colourAt(step));
		frame.stem[i] = baseArrayStem
	}
	return frame;
}

app.get('/state', function(req, res) {
	res.send(setState());
});

// A handler for data coming from the Weight Sensors
app.post('/weightsensor', function(req, res) {
	var sensorNumber = req.body.sensor;
	var sensorValue = req.body.data;
	var steppedOn = weightSensorInterface.registerNewData(sensorNumber, sensorValue);
	if(steppedOn) {
		console.log("Stepped On!");
		padInterface.green();
	}
	else {
		padInterface.red();
	}
	res.sendStatus(200);
});


/// catch 404 and forward to error handler
app.use(function(req, res, next) {
    var err = new Error('Not Found!');
    err.status = 404;
    next(err);
});

app.listen(app.get('port'), function(){
	console.log('Express server listening on port ' + app.get('port'));
});
