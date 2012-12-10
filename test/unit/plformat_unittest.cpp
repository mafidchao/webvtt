#include "payload_testfixture"
class PayloadFormat : public PayloadTest {};

/*
 * Verifies that a cue text span with no tags will parse correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text-span (11/27/2012)
 */
TEST_F(PayloadFormat,DISABLED_BasicCueText)
{
	loadVtt( "payload/payload-format/basic-cue-text.vtt", 1 );
	ASSERT_EQ( Node::Text, getHeadOfCue( 0 )->child( 0 )->kind() );
}

/*
 * Verifies that multiple cue components can be put in one line.
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-components
 */
TEST_F(PayloadFormat,DISABLED_MultipleCueTextTag)
{
	loadVtt( "payload/payload-format/multiple-cue-tag.vtt", 1 );
	ASSERT_TRUE( getHeadOfCue( 0 )->toInternalNode()->childCount() == 5 );
}

/*
 * Verifies that a cue text span with multiple lines will work.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (11/27/2012)
 *	Cue text text consists of one or more cue text components optionally separated by a single line terminator which can be: 
 *		1. CR (U+000D)
 *		2. LF (U+000A)
 *		3. CRLF pair
 */
TEST_F(PayloadFormat,DISABLED_MultilineBasicCueText)
{
	loadVtt( "payload/payload-format/multiline-basic-cue-text.vtt", 1 );
	ASSERT_EQ( Node::Text, getHeadOfCue( 0 )->child( 0 )->kind() );
}

/*
 * Verifies that cue text with single line feed characters will be parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (11/27/2012)
 *	Cue text text consists of one or more cue text components optionally separated by a single line terminator which can be: 
 *		1. CR (U+000D)
 *		2. LF (U+000A)
 *		3. CRLF pair
 */
TEST_F(PayloadFormat,DISABLED_MultilineCueText)
{
	loadVtt( "payload/payload-format/multiline-cue-text.vtt", 1 );
	ASSERT_TRUE( getHeadOfCue( 0 )->toInternalNode()->childCount() == 4 );
}

/*
 * Verifies that multiple cue component are parsed correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (11/27/2012)
 *	Cue text text consists of one or more cue text components optionally separated by a single line terminator which can be: 
 *		1. CR (U+000D)
 *		2. LF (U+000A)
 *		3. CRLF pair
 */
TEST_F(PayloadFormat,DISABLED_MultilineMultipleCueTextTag)
{
	loadVtt( "payload/payload-format/multiline-multiple-cue-text-tag.vtt" );
	
	const InternalNode *node = getHeadOfCue( 0 );
	ASSERT_EQ( Node::Underline, node->kind() );

	node = node->child( 0 )->toInternalNode();
	ASSERT_EQ( Node::Italic, node->kind() );

	node = node->child( 0 )->toInternalNode();
	ASSERT_EQ( Node::Bold, node->kind() );
}

/*
 * Verifies that cue text separated by a CR line terminator is parsed correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (12/02/2012)
 *	Cue text consists of one or more cue text components optionally separated by a single line terminator which can be: 
 *		1. CR (U+000D)
 *		2. LF (U+000A)
 *		3. CRLF pair
 */
TEST_F(PayloadFormat,DISABLED_MultilineBasicCueTextCR)
{
	loadVtt( "payload/payload-format/multiline-basic-cue-text-cr.vtt" );
	ASSERT_EQ( Node::Text, getHeadOfCue( 0 )->child( 0 )->kind() );
}

/*
 * Verifies that cue text separated by a CRLF line terminator is parsed correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (12/02/2012)
 *	Cue text consists of one or more cue text components optionally separated by a single line terminator which can be: 
 *		1. CR (U+000D)
 *		2. LF (U+000A)
 *		3. CRLF pair
 */
TEST_F(PayloadFormat,DISABLED_MultilineBasicCueTextCRLF)
{
	loadVtt( "payload/payload-format/multiline-basic-cue-text-crlf.vtt" );
	ASSERT_EQ( Node::Text, getHeadOfCue( 0 )->child( 0 )->kind() );
}

/* Verifies that cue text with a malformed line terminator is still parsed correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-parser-algorithm (12/02/2012)
 * The WebVTT parser algorithm is as follows:
 * [...] 50. Bad cue: Discard cue.
 */
TEST_F(PayloadFormat,DISABLED_MultilineBasicCueTextExtraLine)
{
	loadVtt( "payload/payload-format/multiline-extra-line-terminator.vtt", 1);
	ASSERT_EQ( Node::Text, getHeadOfCue( 0 )->child( 0 )->kind() );
}