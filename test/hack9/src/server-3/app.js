/**
 * server-3/app.js
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Tim Griesser
 * tgriesser@cs50.harvard.edu
 *
 * Demonstrates a server using socket.io.
 */

var fs = require('fs');
var express = require('express');
var app = express();
var server = app.listen(1337);
var io = require('socket.io').listen(server);

// index.html 
app.get('/', function(req, res) {
    var stream = fs.createReadStream('./index.html');
    stream.on('error', function(err) {
        res.json(400, {error: err.message});
    });
    stream.pipe(res);
});

// sockets
io.sockets.on('connection', function(client) {

    // send a message to the client every five seconds
    setInterval(function() {
        client.emit('from_server', {message: 'Ping ' + new Date()});
    }, 5000);
});
