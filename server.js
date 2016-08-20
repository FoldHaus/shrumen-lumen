var express = require('express');
var bodyParser = require('body-parser');
var engines = require('consolidate');
var mustache = require('mustache');

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

//Add a module containing a class for interacting with the LinearActuator
var LinearActuatorInterface = require("./lib/LinearActuatorInterface.js");
var linearActuatorInterface = new LinearActuatorInterface();

//Add a module containing a class for interacting with the Animations
var AnimationsInterface = require('./lib/AnimationsInterface.js');
var animationsInterface = new AnimationsInterface();

//Add a module containing a class for interacting with the LinearActuator
var InteractionController = require("./lib/InteractionController.js");
var interactionController = new InteractionController(weightSensorInterface, padInterface, linearActuatorInterface, animationsInterface);

//Start animation loop and set and input value in minutes
interactionController.startAnimationLoop(0.5);


app.get('/state', function(req, res) {
	var currentState = animationsInterface.getState();

	res.send({state: currentState});
});

// A handler for data coming from the Weight Sensor Data
app.post('/weightsensor', function(req, res) {
	var sensorNumber = req.body.sensor;
	var sensorValue = req.body.data;
	var steppedOn = weightSensorInterface.registerNewData(sensorValue);
	
	// Add to new thread or do async in the future
	interactionController.handleInteraction();
	res.sendStatus(200);
});


// A handler for data coming from the Linear Actuators
app.get('/linearactuator', function(req, res) {
	var linearActuatorState = linearActuatorInterface.getLinearActuatorState();
	console.log("Linear Actuator State: " + linearActuatorState);
	res.send( {state: linearActuatorState, time: new Date()} );
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
