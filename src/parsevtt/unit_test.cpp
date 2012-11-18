#include <gtest/gtest.h>
extern "C" {
#include <webvtt/parser.h>
}

// Hide main
#define TESTING
#include "parsevtt_main.c"


class MyAppTestSuite : public testing::Test
{
void SetUp(){
}

void TearDown(){}
};


TEST_F(MyAppTestSuite, TEST_webvtt_create_string) {
	webvtt_string *testStr = new webvtt_string();		

    EXPECT_EQ(WEBVTT_SUCCESS, webvtt_create_string(10, testStr));
}

TEST_F(MyAppTestSuite, TEST_create_parser) {	
	const char *input_file = "../../test/unit/sample.vtt";
	webvtt_status result;
	webvtt_parser vtt;
	FILE *fh;		
	
	fh = fopen(input_file,"rb");
	if( !fh )
	{
		fprintf( stderr, "error: failed to open `%s'"
#ifdef WEBVTT_HAVE_STRERROR
		": %s"
#endif
		"\n", input_file
#ifdef WEBVTT_HAVE_STRERROR
		, strerror(errno)
#endif
		);		
	}

	EXPECT_EQ(WEBVTT_SUCCESS, result = webvtt_create_parser( &cue, &error, (void *)input_file, &vtt ));
	
	parse_fh( fh, vtt );
	webvtt_delete_parser( vtt );
	fclose( fh );	
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}