var webvtt = require("./libwebvtt");
var fs = require("fs");
var ref = require('ref');
var Buffer = require('buffer').Buffer;
var util = require('util');

function printParser( parser )
{
  var p = parser;
  console.log( "state: " + p.state + "\nbytes: " + p.bytes + "\nline: " + p.line + "\ncolumn: " + p.column + "\nmode: " + p.mode + "\nfinish: " + (p.finish ? "true" : "false") + "\nflags: " + p.flags + "\ntruncate: " + p.truncate + "\nline_pos: " + p.line_pos + "\ntstate: " + p.tstate + "\ntoken_pos: " + p.token_pos );
}

function parse_fd( fd, buffer, nb, onCue, onError, userData )
{
  var parser, err;
  if( !userData )
  {
    userData = {};
  }

  parser = ref.alloc(webvtt.ParserPtr);
  if( ( err = webvtt.createParser( onCue, onError, userData, parser ) ) != 0  )
  {
    console.log("Error creating webvtt_parser");
    return 1;
  }

  parser = parser.deref();
  userData.parser = parser;
  printParser( parser );
  do
  {
    console.log("parsing " + nb + " bytes.");
    webvtt.parseChunk( parser, buffer, 0, nb );
  } while( (nb = fs.readSync(fd, buffer, 0, buffer.length)) != 0 );

  webvtt.finishParsing( parser );
  webvtt.deleteParser( parser );
}

function remove_comment( fd, buffer, pos, nb )
{
  var start_pos = pos;
  var expectSlash = false;
  var state = 0;
  var b = start_pos;
  do
  {
    while( pos < nb )
    {
      var c = buffer[pos];
      switch( state )
      {
      case 0:
        if( expectSlash && c == 0x2F )
        {
          // found the end of the slash, now we need the newline
          state = 1;
        }
        else if( c == 0x2A )
        {
          expectSlash = true;
        }
        else if( expectSlash )
        {
          expectSlash = false;
        }
        break;

      case 1:
        if( c == 0x0D )
        { // CR
          state = 2;
        }
        else if( c == 0x0A )
        {
          // Just an LF
          state = 3;
        }
        else
        {
          // There was no newline found, but continue anyway.
          state = 3;
          continue;
        }
        break;

      case 2:
        if( c == 0x0A )
        { // CRLF
          state = 3;
        }
        else
        { // Just a CR
          state = 3;
          continue;
        }
        break;

      case 3:
        // found what we're looking for.
        var len = nb - pos;
        if( pos != 0 )
        {
          buffer.copy(buffer, 0, pos, len);
        }
        console.log("Removed " + (b + 2) + " bytes of comments");
        return len;
      }
      ++pos;
      ++b;
    }
    pos = 0;
  } while( (nb = fd.readSync(fd, buffer, 0, buffer.length)) != 0 )
  return 0;
}

exports.parseTestFile = function(fileName, onCue, onError, userData)
{
  var err = 0, fd, buffer, nb, pos;
  if( typeof(fileName) !== "string" || fileName.length == 0 )
  {
    console.log("parse_test called with invalid parameter `fileName':");
    if( typeof(fileName) !== "string" )
    {
      console.log("  received type \"" + typeof(fileName) + "\", expected \"string\"");
    }
    else
    {
      console.log("  \"" + fileName + "\" is empty");
    }
    err = 1;
  }

  if( typeof(onCue) !== "function" )
  {
    console.log("parse_test called with invalid parameter `onCue':");
    console.log("  received type \"" + typeof(onCue) + "\", expected \"function\"");
    err = 1;
  }

  if( onError && typeof(onError) !== "function" )
  {
    console.log("parse_test called with invalid parameter `onError':");
    console.log("  received type \"" + typeof(onError) + "\", expected \"function\"");
    err = 1;
  }

  if( userData && typeof(userData) !== "object" )
  {
    console.log("parse_test called with invalid parameter `userData':");
    console.log("  received type \"" + typeof(userData) + "\", exected \"object\"");
    err = 1;
  }

  if( err !== 0 )
  {
    return err;
  }

  fd = fs.openSync( fileName, "r" );
  if( !fd )
  {
    console.log( "failed to open file `" + fileName + "'");
    return 1;
  }

  buffer = new Buffer(0x4000);

  // skip .test file comment
  nb = fs.readSync(fd, buffer, 0, 0x4000);
  if( nb > 2 && buffer[0] == 0x2F && buffer[1] == 0x2A ) // Found /* with no utf-8 BOM
  {
    nb = remove_comment( fd, buffer, 2, nb );
  }
  else if( nb > buffer[3] == 0x2F && buffer[4] == 0x2A ) // Found /* with utf-8 BOM
  {
    nb = remove_comment( fd, buffer, 5, nb );
  }

  if( nb == 0 )
  {
    // We reached the end of file with no VTT data! Why are we testing this file!
    return 1;
  }

  err = parse_fd( fd, buffer, nb, onCue, onError, userData );

  fs.close(fd);
  return err;
}

exports.webvtt = webvtt;

