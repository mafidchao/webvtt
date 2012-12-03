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
	ASSERT_ANY_THROW( loadVtt( "filestructure/text-before-header.vtt" ) );
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

TEST_F(FileStructure,HeaderNoNewLine)
{
	loadVtt( "filestructure/header-no-new-line.vtt" );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}
TEST_F(FileStructure,NoPayloadText)
{
	loadVtt( "filestructure/no-payload-text.vtt", 2 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}
TEST_F(FileStructure,MissingCueIdentifier)
{
	loadVtt( "filestructure/missing-cue-identifier.vtt", 0 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}