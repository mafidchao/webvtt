var harness = require("./unit-test");
var webvtt = harness.webvtt;
var testCase = require('nodeunit').testCase;

function onCue( userData, cue )
{
  console.log("onCue");
  test.expect( 1 );
  test.equal( cue.from, 11.0, "Timestamp beginning matches expected value" );
  test.done();
}

function onError( userData, error )
{
  console.log("Parse error");
  return -1;
}

harness.parseTestFile( '../spec/good/tc0000-sample_test.test', onCue, onError );
