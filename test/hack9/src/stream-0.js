/**
 * stream-0.js
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Demonstrates stream.
 */

var fs = require('fs');
var http = require('http');

// listen on port 1337
http.createServer(function(req, res) {

    // check whether path exists
    var path = '.' + req.url;
    fs.stat(path, function(err, stats) {
        if (err !== null) {
            res.writeHead(404);
            res.end(err.message);
            return;
        }

        // check whether path is file
        if (!stats.isFile()) {
            res.writeHead(403);
            res.end();
            return;
        }

        // stream file
        var stream = fs.createReadStream(path);
        stream.on('data', function(data) {
            res.write(data);
            console.log('read');
        });
        stream.on('end', function() {
            res.end();
        });
    });
}).listen(1337);
