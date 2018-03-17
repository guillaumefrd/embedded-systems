'use strict';
module.exports = function(app) {
  var data = require('../controllers/dataController');
  var message = require('../controllers/messageController');

  app.route('/data')
    .get(data.list_all_data)
    .post(data.create_a_data);

  app.route('/data/delete')
    .delete(data.delete_all_data);

  app.route('/message')
    .post(message.notify_slack);

    app.route('/message/delete')
      .delete(message.delete_all_messages);
};
