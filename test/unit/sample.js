var libwebvtt = require("./libwebvtt");

var ref = require('ref');
var ffi = require('ffi');

exports.testTester = function(test) {
  test.expect(1);
  test.ok(true, "the test actually ran");
  test.done();
};

var testFileData;


fs.readFile( __dirname + '/../spec/good/tc0000-sample_test.test', function (err, data) {
  if (err) {
    console.log("Error happened! Oh no!");
    throw err;
  }
  console.log("Error did not happen! Oh yeah!");
  testFileData = data;
  //Important: Nodeunit will NOT see any tests that are inside this function
});

exports.test1 = function(test) {
  console.log("report point 1 hit");
  //This is the callback function that will end up being run if the parser succeeds
  var success_callback = ffi.Callback(
    ref.types.void,
    //This first parameter here is apparently supposed to be userdata in the successful case, based on
    //what I saw in parsevtt_main.c
    [ ref.types.Object, libwebvtt.webvtt_cue ],
    function(retval, params) {
      console.log("report point 2 hit");
      //Important to tell it how many tests should be run so that you don't miss any
      test.expect(1);
      //TODO: Find out if params[0] is a webvtt_cue or a set of webvtt cues
      test.equal(params[0].from, 11, "Timestamp beginning matches expected value");
      test.done();
    }
  );

  console.log("report point 3 hit");

  var failure_callback = ffi.Callback(
    'int',
    [ ref.types.Object, webvtt_uint, webvtt_uint, webvtt_int ],
    function(retval, params){
      console.log("report point 4 hit");
      test.expect(1);
      test.ok(false, "The parsing failed at line " + params[1] + ", column " + params[2] + ", with error code " + params[3]);
      test.done();
      retval = -1;
    }
  );

  console.log("report point 5 hit");
  //Allocate space for a webvtt_parser struct and put a pointer to it in parser
  var parser = libwebvtt.ref.alloc(libwebvtt.ref.refType(libwebvtt.webvtt_parser));

  //TODO: Find out what *userdata is supposed to be and if ref.types.void is an acceptable substitute
  libwebvtt.libwebvtt.webvtt_create_parser(success_callback, failure_callback, libwebvtt.ref.types.void, parser);
  //We should now have a parser! Awesome! Now de-reference it and send it in to parse_chunk along with our data
  //TODO: Find out how to get the data into a format that the chunk parser will like
  libwebvtt.libwebvtt.webvtt_parse_chunk(parser.deref(), data, data.length);
};