'use strict';
var mongoose = require('mongoose');
var Schema = mongoose.Schema;


var DataSchema = new Schema({
  temperature: Number,
  humidity: Number,
  luminosity: Number,
  datetime: { type: Date, default: Date.now },
});
var MessageSchema = new Schema({
  message: String,
  datetime: { type: Date, default: Date.now },
});

module.exports = mongoose.model('Data', DataSchema);
module.exports = mongoose.model('Message', MessageSchema);
