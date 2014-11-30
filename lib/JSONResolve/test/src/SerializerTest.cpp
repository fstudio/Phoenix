#include "SerializerTest.hpp"

#include <string>

using namespace std;
using namespace mjson;

void SerializerTest::SetUp()
{

}

TEST_F(SerializerTest, DoubleQuotesInString)
{
    Value value("\"");
    ASSERT_EQ("\"", value.ToString());
}

TEST_F(SerializerTest, DoubleQuotesObjectKey)
{
    Value value;
    value.SetValueForKey("\"", 42);
    ASSERT_EQ("{\"\\\"\":42}", value.ToJSONString());
}
