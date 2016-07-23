var express = require('express');
var app = express();
app.configure(function(){
	app.use(express.bodyParser());
});

app.get('/', function(req, res) {
  res.send('Hello Seattle\n');
});
app.post('/weightsensor', function(req, res){
	console.log(req.body);
	res.send('1');
});
app.listen(3001);
console.log('Listening on port 3001...');
