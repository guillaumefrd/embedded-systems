'use strict';


var mongoose = require('mongoose'),
  Data = mongoose.model('Data');

exports.list_all_data = function(req, res) {
  Data.find({}, function(err, data) {
    if (err)
      res.send(err);
    res.json(data);
  });
};

exports.create_a_data = function(req, res) {
  var new_data = new Data(req.body);
  new_data.save(function(err, data) {
    if (err){
      res.send(err);
    }
    else{
      res.json(data);
    }
  });
};

exports.delete_all_data = function(req, res) {
  Data.remove({}, function(err, data) {
    if (err)
      res.send(err);
    res.json({ message: 'Data successfully deleted' });
  });
};
