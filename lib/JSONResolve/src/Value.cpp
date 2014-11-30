#include <mjson/Value.hpp>
#include <mjson/Utilities.hpp>
#include <sstream>
#include <stdexcept>

using namespace mjson;
using namespace std;

Value Value::nullValue;

string Value::emptyString;

Value::Value()
{
    type = ValueType::Null;
}

Value::Value(double number)
{
    type = ValueType::Number;
    this->number = number;
}

Value::Value(float number)
{
    type = ValueType::Number;
    this->number = static_cast<double>(number);
}

Value::Value(int number)
{
    type = ValueType::Number;
    this->number = static_cast<double>(number);
}

Value::Value(const string &string)
{
    type = ValueType::String;
    this->stringValue = string;
}

Value::Value(const char *string)
{
    type = ValueType::String;
    this->stringValue = string;
}

Value::Value(bool boolean)
{
    type = ValueType::Boolean;
    this->boolean = boolean;
}

ValueType::ValueType Value::GetValueType() const
{
    return type;
}

const Value& Value::GetWithKey(const string& key) const
{
    if(type != ValueType::Object)
    {
        return nullValue;

//        string errorMessage = "Cannot get key ";
//        errorMessage += key;
//        errorMessage += " from a non-object value.";
//        throw TypeMismatchException(errorMessage);
    }

    try
    {
        return objectValues.at(key);
    }
    catch (out_of_range& e)
    {
        return nullValue;
        //throw InvalidKeyException(key);
    }
}

const Value& Value::GetAtIndex(int index) const
{
    if(type == ValueType::Array)
    {
        int arraySize = arrayValues.size();
        if(index < 0 || index >= arraySize)
        {
            return nullValue;
        }
        return arrayValues.at(index);
    }
    else if(type == ValueType::Object)
    {
        int length = objectValues.size();
        if(index < 0 || index >= length)
        {
            return nullValue;
        }
        return GetWithKey(objectKeys[index]);
    }

    return nullValue;
}

const string& Value::GetKey(int index) const
{
    if(index < 0 || index >= objectKeys.size())
    {
        return emptyString;
    }

    return objectKeys[index];
}

bool Value::ContainsKey(const string &key)
{
    if(type != ValueType::Object)
    {
        return false;
    }

    return objectValues.find(key) != objectValues.end();
}

int Value::GetLength() const
{
    switch(type)
    {
    case ValueType::Array:
        return arrayValues.size();
        break;
    case ValueType::Object:
        return objectValues.size();
        break;
    default:
        return 0;
        break;
    }
}

double Value::ToDouble() const
{
    if(type != ValueType::Number)
    {
        return 0;
    }
    return number;
}

float Value::ToFloat() const
{
    if(type != ValueType::Number)
    {
        return 0;
    }
    return static_cast<float>(number);
}

int Value::ToInt() const
{
    if(type != ValueType::Number)
    {
        return 0;
    }
    return static_cast<int>(number);
}

string Value::ToString() const
{
    if(type != ValueType::String)
    {
        return string();
    }
    return stringValue;
}

bool Value::ToBoolean() const
{
    if(type != ValueType::Boolean)
    {
        return false;
    }
    return boolean;
}

bool Value::Push(const Value &value)
{
    if(type != ValueType::Null && type != ValueType::Array)
    {
        return false;
    }
    type = ValueType::Array;
    arrayValues.push_back(value);
    return true;
}

bool Value::SetValueForKey(const string &key, const Value &value)
{
    if(type != ValueType::Null && type != ValueType::Object)
    {
        return false;
    }
    type = ValueType::Object;
    pair<ObjectContainer::iterator, bool> result = objectValues.insert(make_pair(key, value));
    if(result.second)
    {
        //If a new value was create it add it to our object array
        objectKeys.push_back(key);
    }
    return true;
}

string Value::ToJSONString() const
{
    switch(type)
    {
    case ValueType::Array:
        return ArrayValueToString();
        break;
    case ValueType::Object:
        return ObjectValueToString();
        break;
    case ValueType::Number:
        return NumberValueToString();
        break;
    case ValueType::String:
        return StringValueToJSONString();
        break;
    case ValueType::Boolean:
        return BooleanValueToString();
        break;
    case ValueType::Null:
        return "null";
        break;
    }
	return "null";
}

/*
 *
 * Private
 *
 *
 */

string Value::ArrayValueToString() const
{
    string outString("[");
    int arrayLength = arrayValues.size();
    for(int i = 0; i < arrayLength; ++i)
    {
        outString += arrayValues.at(i).ToJSONString();
        if(i+1 < arrayLength)
        {
            outString += ",";
        }
    }
    outString += "]";
    return outString;
}

string Value::ObjectValueToString() const
{
    string outString = "{";
    for(ObjectContainer::const_iterator it = objectValues.begin(); it != objectValues.end(); ++it)
    {
        outString += AsValidJSONString(it->first);
        outString += ":";
        outString += it->second.ToJSONString();
        ObjectContainer::const_iterator nextIt = it;
        ++nextIt;
        if(nextIt != objectValues.end())
        {
            outString += ",";
        }
    }
    outString += "}";
    return outString;
}

string Value::NumberValueToString() const
{
    ostringstream stream;
    stream << number;
    return stream.str();
}

string Value::BooleanValueToString() const
{
    if(boolean)
    {
        return "true";
    }
    else
    {
        return "false";
    }
}

string Value::StringValueToJSONString() const
{
    return AsValidJSONString(stringValue);
}

string Value::AsValidJSONString(const string& in)
{
    string outString = in;

    // Replace longer backslash token first.
    Utilities::ReplaceAll(outString, "\\", "\\\\");
    Utilities::ReplaceAll(outString, "\"", "\\\"" );
    Utilities::ReplaceAll(outString, "/", "\\/");
    Utilities::ReplaceAll(outString, "\b", "\\b");
    Utilities::ReplaceAll(outString, "\f", "\\f");
    Utilities::ReplaceAll(outString, "\n", "\\n");
    Utilities::ReplaceAll(outString, "\r", "\\r");
    Utilities::ReplaceAll(outString, "\t", "\\t");
    //TODO: Unicode
    outString.insert(0, "\"");
    outString += "\"";
    return outString;
}



string Value::CreateTypeMismatchString(const std::vector<ValueType::ValueType> &expected, ValueType::ValueType got)
{
    string errorMessage;
    int expectCount = expected.size();
    if(expectCount <= 0)
    {
        errorMessage = GetValueTypeName(got);
        errorMessage += " is not the correct type.";
        return errorMessage;
    }

    errorMessage = "Expected ";
    for(int i = 0; i < expectCount; ++i)
    {
        errorMessage += GetValueTypeName(expected[i]);
        if(i+1 < expectCount)
        {
            errorMessage += " or ";
        }
    }
    errorMessage += ", got ";
    errorMessage += GetValueTypeName(got);
    errorMessage += ".";

    return errorMessage;
}
