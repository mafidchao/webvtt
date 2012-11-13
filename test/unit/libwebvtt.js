var ref = require('ref');
var refStruct = require('ref-struct');
var ffi = require('ffi');

// define types
var voidPtr = ref.refType(ref.types.void);
var webvtt_int8 = ref.types.int8;
var webvtt_int16 = ref.types.int16;
var webvtt_int32 = ref.types.int32;
var webvtt_int64 = ref.types.int64;
var webvtt_uint8 = ref.types.uint8;
var webvtt_uint16 = ref.types.uint16;
var webvtt_uint32 = ref.types.uint32;
var webvtt_uint64 = ref.types.uint64;
var webvtt_int = ref.types.int;
var webvtt_char = ref.types.char;
var webvtt_short = ref.types.short;
var webvtt_long = ref.types.long;
var webvtt_longlong = ref.types.longlong;
var webvtt_uint = ref.types.uint;
var webvtt_uchar = ref.types.uchar;
var webvtt_ushort = ref.types.ushort;
var webvtt_ulong = ref.types.ulong;
var webvtt_ulonglong = ref.types.ulonglong;
var webvtt_byte = ref.types.uint8;
var webvtt_bool = ref.types.int;
var webvtt_cue = ref.refType(voidPtr);
var webvtt_timestamp = ref.types.double;
var webvtt_length = ref.types.uint32;
var webvtt_status = ref.types.int;
var webvtt_vertical_type = ref.types.int;
var webvtt_align_type = ref.types.int;
var webvtt_cue_fn_ptr = ref.refType(voidPtr);
var webvtt_error_fn_ptr = ref.refType(voidPtr);
var webvtt_bytearray = ref.refType(voidPtr);
var webvtt_node_kind = ref.types.int;
// define structs
var webvtt_parser = refStruct({
  state: webvtt_uint,
  bytes: webvtt_uint,
  line: webvtt_uint,
  column: webvtt_uint,
  read: webvtt_cue_fn_ptr,
  error: webvtt_error_fn_ptr,
  userdata: voidPtr,
  mode: webvtt_bool,
  finish: webvtt_bool,
  flags: webvtt_uint,
  cue: webvtt_cue,
  truncate: ref.types.int,
  line_pos: webvtt_uint,
  line_buffer: webvtt_bytearray,
  tstate: webvtt_uint,
  token_pos: webvtt_uint,
  token: webvtt_byte
});

var webvtt_node = refStruct({
  kind: webvtt_node_kind
});

var webvtt_string = refStruct({
  alloc: webvtt_uint32,
  length: webvtt_uint32,
  text: voidPtr,
  array: voidPtr
});

var webvtt_cue_settings = refStruct({
  vertical: webvtt_vertical_type,
  line_is_relative: webvtt_bool,
  no: webvtt_int,
  relative_position: webvtt_uint,
  position: webvtt_uint,
  size: webvtt_uint,
  align: webvtt_align_type
});

var webvtt_cue = refStruct({
  from: webvtt_timestamp,
  until: webvtt_timestamp,
  settings: webvtt_cue_settings,
  snap_to_lines: webvtt_bool,
  id: webvtt_string,
  payload: webvtt_string,
  text: webvtt_node
});

// create binding to libwebvtt
var libwebvtt = ffi.Library('libwebvtt', {
  'webvtt_parse_chunk': [ webvtt_status, [webvtt_parser, voidPtr, webvtt_uint] ],
  'webvtt_finish_parsing': [ webvtt_status, [webvtt_parser] ],
  'webvtt_parse_cuetext': [ webvtt_status, [ webvtt_parser, webvtt_uint ] ]
});


console.log("Reached end!");
