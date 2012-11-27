#include "payload_testfixture"
class PayloadEscapeCharacter : public PayloadTest {};

/*
 * Verifies that greater than escape characters in the cue text payload are parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-gt-escape (11/27/2012)
 */
TEST_F(PayloadEscapeCharacter,DISABLED_GT)
{
	loadVtt( "payload/escape-character/gt-escape-character.vtt", 1 );

	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();

	String expectedText = String( (const byte *)">", 1 );
	ASSERT_EQ( expectedText.text(), node->content().text() );
}

/*
 * Verifies that less than escape characters in the cue text payload are parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-lt-escape (11/27/2012)
 */
TEST_F(PayloadEscapeCharacter,DISABLED_LT)
{
	loadVtt( "payload/escape-character/lt-escape-character.vtt", 1 );

	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"<", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}

/*
 * Verifies that ampersand escape characters in the cue text payload are parsed correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-amp-escape (11/27/2012)
 */
TEST_F(PayloadEscapeCharacter,DISABLED_Ampsersand)
{
	loadVtt( "payload/escape-character/ampersand-escape-character.vtt", 1 );

	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}

/*
 * Verifies that left to right escape characters are parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-lrm-escape (11/27/2012)
 */
TEST_F(PayloadEscapeCharacter,DISABLED_LRM)
{
	loadVtt( "payload/escape-character/lrm-escape-character.vtt", 1 );

	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	
	ASSERT_EQ( UTF16_LEFT_TO_RIGHT, node->content().text()[0] );
}

/*
 * Verifies that right to left escape characters are parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-rlm-escape (11/27/2012)
 */
TEST_F(PayloadEscapeCharacter,DISABLED_RLM)
{
	loadVtt( "payload/escape-character/rlm-escape-character.vtt", 1 );

	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	
	ASSERT_EQ( UTF16_RIGHT_TO_LEFT, node->content().text()[0] );
}

/*
 * Verifies that non breaking space characters are parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-nbsp-escape (11/27/2012)
 */ 
TEST_F(PayloadEscapeCharacter,DISABLED_NBSP)
{
	loadVtt( "payload/escape-character/nbsp-escape-character.vtt", 1 );

	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	
	ASSERT_EQ( UTF16_NO_BREAK_SPACE, node->content().text()[0] );
}

/*
 * Verifies that multiple escape characters are parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (11/27/2012)
 */
TEST_F(PayloadEscapeCharacter,DISABLED_MultipleEscapeCharacter)
{
	loadVtt( "payload/escape-character/multiple-escape-character.vtt", 1 );

	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	
	ASSERT_EQ( UTF16_NO_BREAK_SPACE, node->content().text()[0] );
	ASSERT_EQ( UTF16_NO_BREAK_SPACE, node->content().text()[1] );
}

/*
 * Verifies that multiple escape characters on multiple lines are parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (11/27/2012)
 *	Cue text text consists of one or more cue text components optionally separated by a single line terminator which can be: 
 *		1. CR (U+000D)
 *		2. LF (U+000A)
 *		3. CRLF pair
 */
TEST_F(PayloadEscapeCharacter,DISABLED_MultilineMultipleEscapeCharacter)
{
	loadVtt( "payload/escape-character/multiline-multiple-escape-character.vtt", 1 );

	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	
	ASSERT_EQ( UTF16_NO_BREAK_SPACE, node->content().text()[0] );
	ASSERT_EQ( UTF16_NO_BREAK_SPACE, node->content().text()[1] );
}