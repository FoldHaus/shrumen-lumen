var express = require('express');
var engines = require('consolidate');
var mustache = require('mustache');

var app = express();

app.set('port', (process.env.PORT || 3000));
app.set('views', __dirname + '/public');
app.set('view engine', 'html');
app.engine('html', engines.mustache);
app.use(express.static(__dirname + '/public'));

var scale = 0;
var step = 0;

function getFrame(step) {
	var frame = {};
	var baseArray = new Array(64).fill(0);
	for(var i = 0; i < 7; i++) {	
		baseArray[step % 64] = 255;
		frame[i] = baseArray
	}	
	return frame;
}
app.get('/', function(req, res) {
	//res.render('home.html')
	
	var dataForLights = {
		colors: [
		  (0xFF * scale) << 16,
		  (0xFF * scale) << 8,
		  0xFF * scale,
		  ((0xFF * scale) << 8) + (0xFF * scale)
		]
	};

	res.send(getFrame(step));
	step++;
	
	scale += 0.01;
	if(scale > 1){
		scale = 0;
	}
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
