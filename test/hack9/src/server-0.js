/**
 * server-0.js
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Demonstrates an HTTP server.
 */

var http = require('http');

// create HTTP server
var server = http.createServer();

// handler for requests
function handler(req, res) {
    res.writeHead(200, {'Content-Type': 'text/plain'});
    res.write('hello, world');
    res.end();
}

// handle requests with handler
server.on('request', handler);

// listen on port 1337
server.listen(1337);
