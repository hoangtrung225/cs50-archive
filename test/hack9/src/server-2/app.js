/**
 * server-2/app.js
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Demonstrates an HTTP server using Express.js.
 */

var express = require('express');
var app = express();

app.listen(1337);

app.get('/*', function(req, res) {
    res.send(200, 'hello, world');
});
