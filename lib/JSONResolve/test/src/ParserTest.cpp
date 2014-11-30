#include "ParserTest.hpp"

#include <string>

using namespace mjson;
using namespace std;

void ParserTest::SetUp()
{
}

TEST_F(ParserTest, EmptyObject)
{
    string emptyObjectString = "{}";
    Value outValue;
    ASSERT_TRUE(parser.Parse(emptyObjectString, &outValue));
    ASSERT_EQ(outValue.GetValueType(), ValueType::Null);
}

TEST_F(ParserTest, ObjectWithWhitespace)
{
    string objectString = "{ \"test\" : 42 }";
    Value outValue;
    bool result = parser.Parse(objectString, &outValue);
    if(!result)
    {
        vector<string> errors = parser.GetErrors();
        for(int i = 0, count = errors.size(); i < count; ++i)
        {
            cout << errors[i] << endl;
        }
    }

    ASSERT_TRUE(result);
    ASSERT_TRUE(parser.Parse(objectString, &outValue));
    ASSERT_EQ(42, outValue.GetWithKey("test").ToInt());
}

TEST_F(ParserTest, GetKeyWithSpaceAtIndex)
{
    string objectString = "{\" \" : \"test\"}";
    Value outValue;
    ASSERT_TRUE(parser.Parse(objectString, &outValue));
    ASSERT_EQ(outValue.GetKey(0), " ");
}

TEST_F(ParserTest, GetValueFromKeyWithSpace)
{
    string objectString = "{\" \" : \"test\"}";
    Value outValue;
    ASSERT_TRUE(parser.Parse(objectString, &outValue));
    Value spaceKeyValue = outValue.GetWithKey(" ");
    ASSERT_NE(spaceKeyValue.GetValueType(), ValueType::Null);
}

TEST_F(ParserTest, GetStringValueContainingSingleSpace)
{
    string objectString = "{\"key\" : \" \"}";
    Value outValue;
    ASSERT_TRUE(parser.Parse(objectString, &outValue));
    ASSERT_EQ(outValue.GetWithKey("key").ToString(), " ");
}

//TODO: ADD TESTS YOU DINGUS
