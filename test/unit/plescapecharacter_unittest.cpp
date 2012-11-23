#include "payload_testfixture"
class PayloadEscapeCharacter : public PayloadTest {};

/*
Verifies that greater than escape characters in the cue text payload are parsed.
Based on the WebVTT cue gt escape specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-gt-escape
*/
TEST_F(PayloadEscapeCharacter,DISABLED_GT)
{
	loadVtt( "payload/escape-character/gt-escape-character.vtt", 1 );

	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)">", 1 );
	ASSERT_EQ( expectedText.text(), node->content().text() );
}

/*
Verifies that less than escape characters in the cue text payload are parsed.
Based on the WebVTT cue lt escape specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-lt-escape
*/
TEST_F(PayloadEscapeCharacter,DISABLED_LT)
{
	loadVtt( "payload/escape-character/lt-escape-character.vtt", 1 );

	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"<", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}

/*
Verifies that ampersand escape characters in the cue text payload are parsed correctly.
Based on the WebVTT cue amp escape specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-amp-escape
*/
TEST_F(PayloadEscapeCharacter,DISABLED_Ampsersand)
{
	loadVtt( "payload/escape-character/ampersand-escape-character.vtt", 1 );

	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}

/*
Verifies that left to right escape characters are parsed.
Based on the WebVTT cue lrm escape specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-lrm-escape
*/
TEST_F(PayloadEscapeCharacter,DISABLED_LRM)
{
	loadVtt( "payload/escape-character/lrm-escape-character.vtt", 1 );

	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	
	ASSERT_EQ( UTF16_LEFT_TO_RIGHT, node->content().text()[0] );
}

/*
Verifies that right to left escape characters are parsed.
Based on the WebVTT cue rlm escape specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-rlm-escape
*/
TEST_F(PayloadEscapeCharacter,DISABLED_RLM)
{
	loadVtt( "payload/escape-character/rlm-escape-character.vtt", 1 );

	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	
	ASSERT_EQ( UTF16_RIGHT_TO_LEFT, node->content().text()[0] );
}

/*
Verifies that non breaking space characters are parsed.
Based on the WebVTT cue nbsp escape specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-nbsp-escape
*/
TEST_F(PayloadEscapeCharacter,DISABLED_NBSP)
{
	loadVtt( "payload/escape-character/nbsp-escape-character.vtt", 1 );

	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	
	ASSERT_EQ( UTF16_NO_BREAK_SPACE, node->content().text()[0] );
}

/*
Verifies that multiple escape characters are parsed.
Based on the WebVTT cue text specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-text
*/
TEST_F(PayloadEscapeCharacter,DISABLED_MultipleEscapeCharacter)
{
	loadVtt( "payload/escape-character/multiple-escape-character.vtt", 1 );

	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	
	ASSERT_EQ( UTF16_NO_BREAK_SPACE, node->content().text()[0] );
	ASSERT_EQ( UTF16_NO_BREAK_SPACE, node->content().text()[1] );
}

/*
Verifies that multiple escape characters on multiple lines are parsed.
This test should pass but is a known fail.

Based on the WebVTT cue chapter title specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-chapter-title-text
*/
TEST_F(PayloadEscapeCharacter,DISABLED_MultilineMultipleEscapeCharacter)
{
	loadVtt( "payload/escape-character/multiline-multiple-escape-character.vtt", 1 );

	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	
	ASSERT_EQ( UTF16_NO_BREAK_SPACE, node->content().text()[0] );
	ASSERT_EQ( UTF16_NO_BREAK_SPACE, node->content().text()[1] );
}