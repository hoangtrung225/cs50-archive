/**
 * async-0.js
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Demonstrates asynchronous methods with callback.
 */

var fs = require('fs');
var http = require('http');

// listen on port 1337
http.createServer(function(req, res) {

    // path to GET
    var p = '.' + req.url;

    // try to read file
    fs.readFile(p, function(err, data) {
        if (err) {
            res.writeHead(500);
            res.end(err.message);
        }
        else {
            res.writeHead(200, {'Content-Type': 'text/plain'});
            res.end(data);
        }
    });
}).listen(1337);
