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

app.listen(app.get('port'), function(){
	console.log('Express server listening on port ' + app.get('port'));
});
