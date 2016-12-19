/**
 * server-1.js
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Demonstrates an HTTP server with less code.
 */

var http = require('http');

// listen on port 1337
http.createServer(function(req, res) {
    res.writeHead(200, {'Content-Type': 'text/plain'});
    res.end('hello, world');
}).listen(1337);
