/**
 * async-2.js
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Demonstrates async.js (and underscore.js).
 */

var async = require('async');
var fs = require('fs');
var http = require('http');
var path = require('path');
var _ = require('underscore');

// listen on port 1337
http.createServer(function(req, res) {

    // path to GET
    var p = path.join('.', req.url);

    // do the following in series
    async.series([

        // check whether path exists
        function(callback) {
            fs.stat(p, function(err, stats) {
                if (err) {
                    return callback(err);
                }
                if (!stats.isFile()) {
                    return callback(new Error('not a file'));
                }
                callback(null);
            });
        },

        // try to read file
        function(callback) {
            fs.readFile(p, function(err, data) {
                if (err) {
                    return callback(err);
                }
                return callback(null, data);
            });
        }
    ], function(err, results) {
        if (err) {
            res.writeHead(400);
            res.end(err.message);
        }
        else {
            res.end(_.last(results));
        }
    });
}).listen(1337);
