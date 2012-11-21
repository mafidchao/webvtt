#include "test_parser"

/*
Verifies that the parser correctly parses a "vertical" key, followed by U+003A ':',
followed by 'rl' (indicating that the text be positioned vertically, and grows towards the left)

From http://dev.w3.org/html5/webvtt/#webvtt-vertical-text-cue-setting (09/28/2012):
	1. The string "vertical".
	2. A U+003A COLON character (:).
	3. One of the following strings: "rl", "lr". 
*/
TEST(WebVTTCueSettingVertical,RL)
{
	try
	{
		ItemStorageParser parser("tc4001-cue_setting_vertical_01_good.vtt");
		parser.parse();
		
		const Cue &cue = parser.getCue(0);
		ASSERT_EQ(cue.isVerticalRightToLeft(),true);
	}
	catch( std::exception e )
	{
		// Something broke.
		ASSERT_TRUE(false);
	}
}

/*
Verifies that the parser correctly parses a "vertical" key, followed by U+003A ':',
followed by 'lr' (indicating that the text be positioned vertically, and grows towards the right)

From http://dev.w3.org/html5/webvtt/#webvtt-vertical-text-cue-setting (09/28/2012):
	1. The string "vertical".
	2. A U+003A COLON character (:).
	3. One of the following strings: "rl", "lr". 
*/
TEST(WebVTTCueSettingVertical,LR)
{
	try
	{
		ItemStorageParser parser("tc4002-cue_setting_vertical_02_good.vtt");
		parser.parse();
		
		const Cue &cue = parser.getCue(0);
		ASSERT_EQ(cue.isVerticalLeftToRight(),true);
	}
	catch( std::exception e )
	{
		// Something broke.
		ASSERT_TRUE(false);
	}
}
