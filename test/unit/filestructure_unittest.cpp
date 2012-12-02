#include "cue_testfixture"
class FileStructure : public CueTest { };
/* Covers the tests for general file structure. 
 * #1001-1019
 *
 * TODO: 1006, 1009, 1010, 1014, 1016, 1017, 1018, 1019
 */

TEST_F(FileStructure,WebVTTNoBOM)
{
	loadVtt( "filestructure/webvtt-no-bom.vtt", 0 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

TEST_F(FileStructure,DISABLED_WebVTTWithBOM)
{
	loadVtt( "filestructure/webvtt-with.bom.vtt" );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

TEST_F(FileStructure,WebVTTSpace)
{
	loadVtt( "filestructure/webvtt-space.vtt" );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

TEST_F(FileStructure,WebVTTTab)
{
	loadVtt( "filestructure/webvtt-tab.vtt" );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

TEST_F(FileStructure,WebVTTTabText)
{
	loadVtt( "filestructure/webvtt-tab-text.vtt" );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

TEST_F(FileStructure,WebVTTSpaceText)
{
	loadVtt( "filestructure/webvtt-space-text.vtt" );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

TEST_F(FileStructure,TextBeforeHeader)
{
	printf ("Opening file...\n");
	parser = new ItemStorageParser( "filestructure/text-before-header.vtt" );
	printf ("Creating parser...\n");
	ASSERT_FALSE( parser->parse() ) << "parser.parse() failed";
     //ASSERT_EQ( expectedNumberOfCues, parser->cueCount() ) << "webvtt file contained different number of cues than expected, once parsed.";
	//loadVtt( "filestructure/text-before-header.vtt" );
	//ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

TEST_F(FileStructure,BlankFile)
{
	loadVtt( "filestructure/blank-file.vtt" );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

TEST_F(FileStructure,DISABLED_BlankFileWithBOM)
{
	loadVtt( "filestructure/blank-file-with-bom.vtt" );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

TEST_F(FileStructure,TabAfterBOMBeforeHeader)
{
	loadVtt( "filestructure/tab-after-bom-before-header.vtt" );
	ASSERT_EQ( 1, errorCount() ) << "This file should contain one error.";
}
