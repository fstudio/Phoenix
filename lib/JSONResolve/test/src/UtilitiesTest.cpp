#include "UtilitiesTest.hpp"

#include <string>
#include <vector>

#include <mjson/Utilities.hpp>

using namespace mjson;
using namespace std;

void UtilitiesTest::SetUp()
{
}

TEST_F(UtilitiesTest, SplitWhitespace)
{
    string testString = "   test   ";
    vector<string> strings;
    Utilities::SplitWhitespace(testString, strings);
    ASSERT_EQ(3, strings.size());
    ASSERT_EQ("   ", strings[0]);
    ASSERT_EQ("test", strings[1]);
    ASSERT_EQ("   ", strings[2]);
}

TEST_F(UtilitiesTest, SplitWhitespaceEmptyString)
{
    string testString = "";
    vector<string> strings;
    Utilities::SplitWhitespace(testString, strings);
    ASSERT_EQ(0, strings.size());
}

TEST_F(UtilitiesTest, SplitWhitespaceAllWhitespace)
{
    string testString = "  ";
    vector<string> strings;
    Utilities::SplitWhitespace(testString, strings);
    ASSERT_EQ(1, strings.size());
    ASSERT_EQ("  ", strings[0]);
}

TEST_F(UtilitiesTest, SplitWhitespaceOneSpaceGaps)
{
    string testString = " 42 ";
    vector<string> strings;
    Utilities::SplitWhitespace(testString, strings);
    ASSERT_EQ(3, strings.size());
    ASSERT_EQ(" ", strings[0]);
    ASSERT_EQ("42", strings[1]);
    ASSERT_EQ(" ", strings[2]);
}

//TODO: ADD TESTS YOU DINGUS
