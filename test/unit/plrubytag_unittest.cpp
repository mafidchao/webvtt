#include "payload_testfixture"
class PayloadRubyTag : public PayloadTest {};

/**
 * Verifies that the parser correctly parses ruby tags.
 * 1. Check standard - <ruby><rt></rt></ruby>
 * 2. Check optional last rt - <ruby><rt></ruby>
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-ruby-span (11/25/2012):
 * A WebVTT cue ruby span consists of the following components, in the order given:
 * 1. A WebVTT cue span start tag "ruby" that disallows an annotation.
 * 2. One or more occurrences of the following group of components, in the order given:
 *  1. WebVTT cue internal text, representing the ruby base.
 *  2. A WebVTT cue span start tag "rt" that disallows an annotation.
 *  3. A WebVTT cue ruby text span: WebVTT cue internal text, representing the ruby text component 
 *     of the ruby annotation.
 *  4. A WebVTT cue span end tag "rt". If this is the last occurrence of this group of components in
 *     the WebVTT cue ruby span, then this last end tag string may be omitted.
 * 3. If the last end tag string was not omitted: Optionally, a WebVTT line terminator.
 * 4. If the last end tag string was not omitted: Zero or more U+0020 SPACE characters or U+0009
 *    CHARACTER TABULATION (tab) characters, each optionally followed by a WebVTT line terminator.
 * 5. A WebVTT cue span end tag "ruby".
 */
TEST_F(PayloadRubyTag,DISABLED_ValidRuby)
{
  loadVtt( "payload/ruby-tag/ruby-cue-component.vtt");

  const InternalNode *head0 = getHeadOfCue( 0 );

  ASSERT_EQ( Node::Ruby, head0->child( 0 )->kind() );
  ASSERT_EQ( Node::RubyText, head0->child( 1 )->toInternalNode()->child( 1 )->kind() );
}

/**
 * Verifies that a ruby tag with an annotation is parsed correctly but does not contain the annotation.
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-ruby-span (11/25/2012):
 * A WebVTT cue ruby span consists of the following components, in the order given:
 * 1. A WebVTT cue span start tag "ruby" that disallows an annotation.
 * 2. One or more occurrences of the following group of components, in the order given:
 *  1. WebVTT cue internal text, representing the ruby base.
 *  2. A WebVTT cue span start tag "rt" that disallows an annotation.
 *  3. A WebVTT cue ruby text span: WebVTT cue internal text, representing the ruby text component 
 *     of the ruby annotation.
 *  4. A WebVTT cue span end tag "rt". If this is the last occurrence of this group of components in
 *     the WebVTT cue ruby span, then this last end tag string may be omitted.
 * 3. If the last end tag string was not omitted: Optionally, a WebVTT line terminator.
 * 4. If the last end tag string was not omitted: Zero or more U+0020 SPACE characters or U+0009
 *    CHARACTER TABULATION (tab) characters, each optionally followed by a WebVTT line terminator.
 * 5. A WebVTT cue span end tag "ruby".
 */
TEST_F(PayloadRubyTag,DISABLED_RubyAnnotation)
{
  loadVtt( "payload/ruby-tag/ruby-annotation.vtt", 1);

  const InternalNode *head = getHeadOfCue( 0 );

  ASSERT_EQ( 0, head->child( 1 )->toInternalNode()->annotation().length() );
  
}

/**
 * Verifies that a ruby text tag with an annotation is parsed correctly but does not contain the annotation.
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-ruby-span (11/25/2012):
 * A WebVTT cue ruby span consists of the following components, in the order given:
 * 1. A WebVTT cue span start tag "ruby" that disallows an annotation.
 * 2. One or more occurrences of the following group of components, in the order given:
 *  1. WebVTT cue internal text, representing the ruby base.
 *  2. A WebVTT cue span start tag "rt" that disallows an annotation.
 *  3. A WebVTT cue ruby text span: WebVTT cue internal text, representing the ruby text component 
 *     of the ruby annotation.
 *  4. A WebVTT cue span end tag "rt". If this is the last occurrence of this group of components in
 *     the WebVTT cue ruby span, then this last end tag string may be omitted.
 * 3. If the last end tag string was not omitted: Optionally, a WebVTT line terminator.
 * 4. If the last end tag string was not omitted: Zero or more U+0020 SPACE characters or U+0009
 *    CHARACTER TABULATION (tab) characters, each optionally followed by a WebVTT line terminator.
 * 5. A WebVTT cue span end tag "ruby".
 */
TEST_F(PayloadRubyTag,DISABLED_RubyTextAnnotation)
{
  loadVtt( "payload/ruby-tag/ruby-text-annotation.vtt" );

  const InternalNode *head = getHeadOfCue( 0 );

  ASSERT_EQ( 0, head->child( 1 )->toInternalNode()->annotation().length() );
}

/**
 * Verifies that a ruby tag with no base text is parsed correctly but does not contain the base text.
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-ruby-span (11/25/2012):
 * A WebVTT cue ruby span consists of the following components, in the order given:
 * 1. A WebVTT cue span start tag "ruby" that disallows an annotation.
 * 2. One or more occurrences of the following group of components, in the order given:
 *  1. WebVTT cue internal text, representing the ruby base.
 *  2. A WebVTT cue span start tag "rt" that disallows an annotation.
 *  3. A WebVTT cue ruby text span: WebVTT cue internal text, representing the ruby text component 
 *     of the ruby annotation.
 *  4. A WebVTT cue span end tag "rt". If this is the last occurrence of this group of components in
 *     the WebVTT cue ruby span, then this last end tag string may be omitted.
 * 3. If the last end tag string was not omitted: Optionally, a WebVTT line terminator.
 * 4. If the last end tag string was not omitted: Zero or more U+0020 SPACE characters or U+0009
 *    CHARACTER TABULATION (tab) characters, each optionally followed by a WebVTT line terminator.
 * 5. A WebVTT cue span end tag "ruby".
 */
TEST_F(PayloadRubyTag,DISABLED_NoRubyBaseText)
{
  loadVtt( "payload/ruby-tag/no-base-text.vtt");

  const InternalNode *head = getHeadOfCue( 0 );

  ASSERT_EQ( Node::Ruby, head->child( 1 )->kind() );
  ASSERT_EQ( Node::RubyText, head->child( 1 )->toInternalNode()->child( 0 )->kind());
}

/**
 * Verifies that a ruby tag without a ruby text tag is parsed correctly but does not contain the
 * ruby text tag.
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-ruby-span (11/25/2012):
 * A WebVTT cue ruby span consists of the following components, in the order given:
 * 1. A WebVTT cue span start tag "ruby" that disallows an annotation.
 * 2. One or more occurrences of the following group of components, in the order given:
 *  1. WebVTT cue internal text, representing the ruby base.
 *  2. A WebVTT cue span start tag "rt" that disallows an annotation.
 *  3. A WebVTT cue ruby text span: WebVTT cue internal text, representing the ruby text component 
 *     of the ruby annotation.
 *  4. A WebVTT cue span end tag "rt". If this is the last occurrence of this group of components in
 *     the WebVTT cue ruby span, then this last end tag string may be omitted.
 * 3. If the last end tag string was not omitted: Optionally, a WebVTT line terminator.
 * 4. If the last end tag string was not omitted: Zero or more U+0020 SPACE characters or U+0009
 *    CHARACTER TABULATION (tab) characters, each optionally followed by a WebVTT line terminator.
 * 5. A WebVTT cue span end tag "ruby".
 */
TEST_F(PayloadRubyTag,DISABLED_NoRubyTextTag)
{
  loadVtt( "payload/ruby-tag/no-ruby-text-tag.vtt", 1 );

  const InternalNode *head = getHeadOfCue( 0 );

  ASSERT_EQ( Node::Ruby, head->child( 1 )->kind() );
  ASSERT_EQ( Node::Text, head->child( 1 )->toInternalNode()->child( 0 )->kind());
}

/**
 * Verifies that a ruby text tag without WebVTT cue internal text representing the ruby text is 
 * parsed correctly but does not contain the ruby text.
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-ruby-span (11/25/2012):
 * A WebVTT cue ruby span consists of the following components, in the order given:
 * 1. A WebVTT cue span start tag "ruby" that disallows an annotation.
 * 2. One or more occurrences of the following group of components, in the order given:
 *  1. WebVTT cue internal text, representing the ruby base.
 *  2. A WebVTT cue span start tag "rt" that disallows an annotation.
 *  3. A WebVTT cue ruby text span: WebVTT cue internal text, representing the ruby text component 
 *     of the ruby annotation.
 *  4. A WebVTT cue span end tag "rt". If this is the last occurrence of this group of components in
 *     the WebVTT cue ruby span, then this last end tag string may be omitted.
 * 3. If the last end tag string was not omitted: Optionally, a WebVTT line terminator.
 * 4. If the last end tag string was not omitted: Zero or more U+0020 SPACE characters or U+0009
 *    CHARACTER TABULATION (tab) characters, each optionally followed by a WebVTT line terminator.
 * 5. A WebVTT cue span end tag "ruby".
 */
TEST_F(PayloadRubyTag,DISABLED_NoRubyText)
{
  loadVtt( "payload/ruby-tag/no-ruby-text.vtt", 2 );

  const InternalNode *head0 = getHeadOfCue( 0 );
  const InternalNode *head1 = getHeadOfCue( 1 );

  ASSERT_EQ( Node::Ruby, head0->child( 1 )->kind() );
  ASSERT_EQ( Node::Text, head0->child( 1 )->toInternalNode()->child( 0 )->kind());
  ASSERT_EQ( Node::RubyText, head0->child( 1 )->toInternalNode()->child( 1 )->kind());
  ASSERT_TRUE( head0->child( 1 )->toInternalNode()->child( 1 )->toInternalNode()->childCount() == 0 );

  ASSERT_EQ( Node::Ruby, head1->child( 1 )->kind() );
  ASSERT_EQ( Node::Text, head1->child( 1 )->toInternalNode()->child( 0 )->kind());
  ASSERT_EQ( Node::RubyText, head1->child( 1 )->toInternalNode()->child( 1 )->kind());
  ASSERT_TRUE( head1->child( 1 )->toInternalNode()->child( 1 )->toInternalNode()->childCount() == 0 );
}

/**
 * Verifies that the parser correctly parses a ruby tag with an optional WEBVTT Line Terminator
 * after a an </rt> tag.
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-ruby-span (11/25/2012):
 * A WebVTT cue ruby span consists of the following components, in the order given:
 * 1. A WebVTT cue span start tag "ruby" that disallows an annotation.
 * 2. One or more occurrences of the following group of components, in the order given:
 *  1. WebVTT cue internal text, representing the ruby base.
 *  2. A WebVTT cue span start tag "rt" that disallows an annotation.
 *  3. A WebVTT cue ruby text span: WebVTT cue internal text, representing the ruby text component 
 *     of the ruby annotation.
 *  4. A WebVTT cue span end tag "rt". If this is the last occurrence of this group of components in
 *     the WebVTT cue ruby span, then this last end tag string may be omitted.
 * 3. If the last end tag string was not omitted: Optionally, a WebVTT line terminator.
 * 4. If the last end tag string was not omitted: Zero or more U+0020 SPACE characters or U+0009
 *    CHARACTER TABULATION (tab) characters, each optionally followed by a WebVTT line terminator.
 * 5. A WebVTT cue span end tag "ruby".
 */
TEST_F(PayloadRubyTag,DISABLED_OptionalLineTerminator)
{
  /*
   * Seg Fault
   */
  loadVtt( "payload/ruby-tag/optional-line-terminator.vtt");
}