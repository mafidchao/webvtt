var ref = require('ref');
var Struct = require('ref-struct');
var ffi = require('ffi');
var assert = require('assert');

// define types
var voidPtr = exports.voidPtr = ref.refType(ref.types.void);
var webvtt_int8 = exports.int8 = ref.types.int8;
var webvtt_int16 = exports.int16 = ref.types.int16;
var webvtt_int32 = exports.int32 = ref.types.int32;
var webvtt_int64 = exports.int64 = ref.types.int64;
var webvtt_uint8 = exports.uint8 = ref.types.uint8;
var webvtt_uint16 = exports.uint16 = ref.types.uint16;
var webvtt_uint32 = exports.uint32 = ref.types.uint32;
var webvtt_uint64 = exports.uint64 = ref.types.uint64;
var webvtt_int = exports.int = ref.types.int;
var webvtt_char = exports.char = ref.types.char;
var webvtt_short = exports.short = ref.types.short;
var webvtt_long = exports.long = ref.types.long;
var webvtt_longlong = exports.longlong = ref.types.longlong;
var webvtt_uint = exports.uint = ref.types.uint;
var webvtt_uchar = exports.uchar = ref.types.uchar;
var webvtt_ushort = exports.ushort = ref.types.ushort;
var webvtt_ulong = exports.ulong = ref.types.ulong;
var webvtt_ulonglong = exports.ulonglong = ref.types.ulonglong;
var webvtt_byte = exports.byte = ref.types.uint8;
var webvtt_bool = exports.bool = ref.types.int;
var webvtt_timestamp = exports.timestamp = ref.types.double;
var webvtt_length = exports.length_t = ref.types.uint32;
var webvtt_status = exports.status_t = ref.types.int;
var webvtt_vertical_type = ref.types.int;
var webvtt_align_type = ref.types.int;
var webvtt_bytearray = ref.refType(voidPtr);
var webvtt_node_kind = ref.types.int;

// define structs
var webvtt_node = exports.node = Struct({
  kind: webvtt_node_kind
});

var webvtt_string = Struct({
  alloc: webvtt_uint32,
  length: webvtt_uint32,
  text: voidPtr,
  array: voidPtr
});

var webvtt_cue_settings = Struct({
  vertical: webvtt_vertical_type,
  line_is_relative: webvtt_bool,
  no: webvtt_int,
  relative_position: webvtt_uint,
  position: webvtt_uint,
  size: webvtt_uint,
  align: webvtt_align_type
});

var webvtt_cue = Struct({
  from: webvtt_timestamp,
  until: webvtt_timestamp,
  settings: webvtt_cue_settings,
  snap_to_lines: webvtt_bool,
  id: webvtt_string,
  payload: webvtt_string,
  text: webvtt_node
});

var webvtt_parser = Struct({
  state: webvtt_uint,
  bytes: webvtt_uint,
  line: webvtt_uint,
  column: webvtt_uint,
  read: voidPtr,
  error: voidPtr,
  userdata: voidPtr,
  mode: webvtt_bool,
  finish: webvtt_bool,
  flags: webvtt_uint,
  cue: webvtt_cue,
  truncate: 'int',
  line_pos: webvtt_uint,
  line_buffer: webvtt_bytearray,
  tstate: webvtt_uint,
  token_pos: webvtt_uint,
  token: webvtt_byte
});

exports.Parser_t = webvtt_parser;
exports.Parser = ref.refType(exports.Parser_t);
exports.ParserPtr = ref.refType(exports.Parser);
exports.Cue = webvtt_cue;
exports.String = webvtt_string;
exports.CueSettings = webvtt_cue_settings;
exports.Node = webvtt_node;

// Fix these
exports.InternalNode = webvtt_node;
exports.LeafNode = webvtt_node;

// Callbacks
var webvtt_cue_fn_ptr = ffi.Function( 'void', [ ref.types.Object, webvtt_cue ] );
var webvtt_error_fn_ptr = ffi.Function( 'int', [ ref.types.Object, webvtt_uint, webvtt_uint, webvtt_int ] );

// create binding to libwebvtt
var libwebvtt = ffi.Library('libwebvtt', {
  'webvtt_parse_chunk': [ webvtt_status, [webvtt_parser, ref.types.Object, webvtt_uint] ],
  'webvtt_finish_parsing': [ webvtt_status, [webvtt_parser] ],
  'webvtt_parse_cuetext': [ webvtt_status, [ webvtt_parser, webvtt_uint ] ],
  'webvtt_create_parser': [webvtt_status, [webvtt_cue_fn_ptr, webvtt_error_fn_ptr, ref.types.Object, exports.ParserPtr ]],
  'webvtt_delete_parser': [ref.types.void, [webvtt_parser]]
});

// exported parser creation function, do keep the messy details hidden
exports.createParser = function( onCue, onError, userData, parser )
{
  var onCueFn, onErrorFn, ret;
  try
  {
    onCueFn = webvtt_cue_fn_ptr.toPointer(onCue);
  }
  catch(e)
  {
    console.log( "error@createParser(): " + e.message );
  }

  if( onError )
  {
    try
    {
      onErrorFn = webvtt_error_fn_ptr.toPointer(onError);
    }
    catch(e)
    {
      console.log( "error@createParser(): " + e.message );
    }
  }
  try
  {
    ret = libwebvtt.webvtt_create_parser( onCueFn, onErrorFn, userData, parser );
  }
  catch(e)
  {
    console.log( "error@createParser(): " + e.message );
    ret = 1;
  }
  return ret;
}

exports.deleteParser = function( parser )
{
  libwebvtt.webvtt_delete_parser( parser );
}

exports.parseChunk = function( parser, buffer, size )
{
  try
  {
    assert.equal(parser.type, exports.Parser, "error@parseChunk(): expected Parser for parameter 1" );
    return libwebvtt.webvtt_parse_chunk( parser, buffer, size );
  }
  catch(e)
  {
    console.log( "error@parseChunk(): " + e.message );
  }
}

exports.finishParsing = function( parser )
{
  return libwebvtt.webvtt_finish_parsing( parser );
}

exports.parseCuetext = function( parser, line, buffer, len, node )
{
  return libwebvtt.webvtt_parse_cuetext( parser, line, buffer, len, node );
}
