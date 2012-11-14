var harness = require("./unit-test");
var webvtt = harness.webvtt;
var testCase = require('nodeunit').testCase;
var ffi = require('ffi');
var ref = require('ref');

exports.sampleTest = function(test) {
  function onCue( userData, cue )
  {
    console.log("onCue");
    test.expect( 1 );
    test.equal( cue.from, 11.0, "Timestamp beginning matches expected value" );
    test.done();
  }

  function onError( userData, line, column, error )
  {
    console.log("Parse error");
    return -1;
  }

  var success_callback = ffi.Callback(
    ref.types.void,
    [ ref.types.Object, webvtt.Cue ],
    function(retval, params) {
      retval = onCue(params[0], params[1]);
    }
  );

  var failure_callback = ffi.Callback(
    'int',
    [ ref.types.Object, webvtt.uint, webvtt.uint, webvtt.int ],
    function(retval, params){
      retval = onCue(params[0], params[1], params[2], params[3]);
    }
  );

  harness.parseTestFile( 'test/spec/good/tc0000-sample_test.test', success_callback, failure_callback );
}