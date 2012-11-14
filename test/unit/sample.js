var libwebvtt = require("./libwebvtt");

var ref = require('ref');
var ffi = require('ffi');

exports.testTester = function(test) {
  test.expect(1);
  test.ok(true, "the test actually ran");
  test.done();
};
