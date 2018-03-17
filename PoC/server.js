Slack = require('node-slackr');
var express = require('express'),
  app = express(),
  port = process.env.PORT || 3000,
  mongoose = require('mongoose'),
  Task = require('./api/models/dataModel'),
  bodyParser = require('body-parser');

// mongoose instance connection url connection
mongoose.Promise = global.Promise;
mongoose.connect('mongodb://localhost/ESAP_data');

//SlackBOT
slack = new Slack('https://hooks.slack.com/services/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',{
  channel: "#bot_notifications",
  username: "EmbeddedSystemsBOT",
  icon_emoji: ":ghost:"
});

app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

app.use(express.static('public'));
app.get('/projetESAP',function(req,res){
	res.sendFile( __dirname +"/public/" +"index.html");
})

var routes = require('./api/routes/dataRoutes'); //importing route
routes(app); //register the route


app.listen(port);

console.log('ESAP data RESTful API server started on: ' + port);
