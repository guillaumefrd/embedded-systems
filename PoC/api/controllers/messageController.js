'use strict';


var mongoose = require('mongoose'),
  Message = mongoose.model('Message');

exports.notify_slack = function(req, res) {
  var new_message = new Message(req.body);
  slack.notify(new_message.message);
  new_message.save(function(err, data) {
    if (err)
      res.send(err);
    res.json(data);
  });
};

exports.delete_all_messages = function(req, res) {
  Message.remove({}, function(err, data) {
    if (err)
      res.send(err);
    res.json({ message: 'Messages successfully deleted' });
  });
};
