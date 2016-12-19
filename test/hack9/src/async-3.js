/**
 * async-3.js
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Demonstrates async.js (and underscore.js) with less code.
 */

var async = require('async');
var fs = require('fs');
var http = require('http');
var path = require('path');

// listen on port 1337
http.createServer(function(req, res) {

    // path to GET
    var p = path.join('.', req.url);

    // do the following via waterfall (in series)
    async.waterfall([

        // check whether path exists
        function(callback) {
            fs.stat(p, callback);
        },

        function(stats, callback) {
            if (!stats.isFile()) {
                var e = new Error('not a file');
                e.code = 403;
                return callback(e);
            }
            callback(null);
        },

        // try to read file
        function(callback) {
            fs.readFile(p, callback);
        }
    ], function(err, result) {
        if (!err) {
            res.writeHead(err.code || 400);
            res.end(err.message);
        }
        else {
            res.end(result);
        }
    });
}).listen(1337);
