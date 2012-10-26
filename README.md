WebVTT is a caption and subtitle format designed for use with HTML5
audio and video elements.

See http://www.whatwg.org/specs/web-apps/current-work/webvtt.html

This is a parser library which implements the format. My intent
is for it to be the foundation of the text track implementation
in Mozilla Firefox. Hopefully it will be useful to others as well.

Right now, nothing works. I'm doing a quick and dirty parser
for now so I can get on with the API design and associated
integration work, then spiff it up into a full, compliant
parser.

Current build status:

https://travis-ci.org/mafidchao/webvtt.png
"!https://travis-ci.org/mafidchao/webvtt.png!":https://travis-ci.org/mafidchao/webvtt
![Testing Travis CI](https://travis-ci.org/mafidchao/webvtt.png "Build Status")