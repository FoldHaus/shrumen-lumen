var express = require('express');
var app = express();
var bodyParser = require('body-parser');

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
	extended: true
}));

app.get('/', function(req, res) {
  res.send('Hello Seattle\n');
});
app.post('/weightsensor', function(req, res){
	console.log("got a post");
	console.log(req.body);
	res.send('1');
});
app.listen(3001);
console.log('Listening on port 3001...');
