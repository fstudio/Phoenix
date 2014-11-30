#include <mjson/Parser.hpp>
#include <vector>
#include <iostream>
#include <mjson/Utilities.hpp>
#include <stack>
#include <math.h>
#include <sstream>

using namespace std;

namespace mjson
{
    class SpecialTokenManager
    {

        vector<string> specialTokens;

    public:

        SpecialTokenManager()
        {
            specialTokens.push_back("[");
            specialTokens.push_back("]");
            specialTokens.push_back("{");
            specialTokens.push_back("}");
            specialTokens.push_back(",");
            specialTokens.push_back(":");
            specialTokens.push_back("\"");
            specialTokens.push_back("'");
            specialTokens.push_back("\n");
        }

        const vector<string>& GetSpecialTokens()
        {
            return specialTokens;
        }

    };

    SpecialTokenManager specialTokenManager;
}

using namespace mjson;

Token Parser::emptyToken(0,0,"");

bool Parser::Parse(const string& input, Value *outValue)
{
    errors.clear();

    const vector<string>& specialTokens = specialTokenManager.GetSpecialTokens();

    list<string> stringTokens;
    stringTokens.push_back(input);

    int specialTokenCount = static_cast<int>(specialTokens.size());
    for(list<string>::iterator it = stringTokens.begin(); it != stringTokens.end();)
    {
        //Get the iterator to the element.
        list<string>::iterator nextIt = it;
        //++nextIt;

        list<string>::iterator insertIterator = it;
        insertIterator++;

        //Get the token we are currently on.
        string currentToken = *it;

        for(int i = 0; i < specialTokenCount; ++i)
        {
            const string& specialToken = specialTokens[i];

            //And Tokenize it.
            vector<string> newTokens;
            Tokenize(currentToken, specialToken, newTokens);
            //Add them to the tokens list
            stringTokens.insert(insertIterator, newTokens.begin() + 1, newTokens.end());
            insertIterator = it;
            insertIterator++;

            currentToken = newTokens[0];
        }

        // Split whitespace into seperate tokens
        vector<string> splitStrings; // TODO: Cached vector
        Utilities::SplitWhitespace(currentToken, splitStrings);

        stringTokens.insert(insertIterator, splitStrings.begin(), splitStrings.end());
        nextIt = it;
        nextIt++;
        nextIt++;

        //And erase the old token.
        stringTokens.erase(it);

        //Set the current iterator to the next element iterator.
        it = nextIt;
    }

    list<Token> tokens;
    int currentLine = 1;
    int currentColumn = 1;

    //Process Tokens, trim whitespace, and store information about them
    for(list<string>::iterator it = stringTokens.begin(); it != stringTokens.end();)
    {
        //Get the next iterator in case we delete the current one.
        list<string>::iterator nextIt = it;
        nextIt++;

        string& token = *it;

        int tokenLength;
        int tokenHeight;

        if(token == "\n")
        {
            tokenLength = 0;
            tokenHeight = 1;
        }
        else
        {
            tokenLength = static_cast<int>(token.size());
            tokenHeight = 0;
        }

        tokens.push_back(Token(currentLine, currentColumn, token));

        currentLine += tokenHeight;
        currentColumn += tokenLength;

        it = nextIt;
    }

    currentTokenIterator = tokens.begin();
    endTokenIterator = tokens.end();

    *outValue = ReadValue();

    if(currentTokenIterator != tokens.end())
    {
        errors.push_back(CreateErrorFromToken(Token(currentLine, currentColumn, ""), "Expected EOF"));
    }

    if(errors.size() > 0)
    {
        return false;
    }
    return true;
}

const vector<string>& Parser::GetErrors()
{
    return errors;
}

/*
 *
 * Private
 *
 *
 */

void Parser::Tokenize(const string &input, const string &delimiter, std::vector<string> &tokens)
{
    size_t lastTokenPosition = 0;
    size_t stringPosition = 0;
    size_t delimiterSize = delimiter.size();
    for(;;)
    {
        stringPosition = input.find(delimiter, stringPosition);
        if(stringPosition == string::npos)
        {
            if(lastTokenPosition != input.size())
            {
                tokens.push_back(string(input, lastTokenPosition, string::npos));
            }
            break;
        }
        else
        {
            if(lastTokenPosition != stringPosition)
            {
                tokens.push_back(string(input, lastTokenPosition, stringPosition - lastTokenPosition));
            }
        }
        tokens.push_back(delimiter);
        stringPosition += delimiterSize + 1;
        lastTokenPosition = stringPosition - 1;
    }
}

const Token& Parser::GetNextToken()
{
    if(currentTokenIterator == endTokenIterator)
    {
        return emptyToken;

    }
    return *currentTokenIterator++;
}


const Token& Parser::GetNextNonWhitespaceToken()
{
    const Token* token = &GetNextToken();
    while(token->ContainsWhitespace())
    {
        token = &GetNextToken();
    }
    return *token;
}

const Token& Parser::PeekToken()
{
    list<Token>::iterator it = currentTokenIterator;
    return *(it++);
}

const Token& Parser::PeekNonWhitespaceToken()
{
    list<Token>::iterator it = currentTokenIterator;
    while(it->ContainsWhitespace())
    {
        it++;
    }
    return *it;
}

void Parser::SkipToken()
{
    ++currentTokenIterator;
}

bool Parser::IsStartOfString(const Token& token)
{
    const string& content = token.GetContent();
    return (content == "\"" || content == "'");
}

bool Parser::IsStartOfObject(const Token &token)
{
    return token.GetContent() == "{";
}

bool Parser::IsStartOfArray(const Token &token)
{
    return token.GetContent() == "[";
}

bool Parser::IsTrue(const Token &token)
{
    return token.GetContent() == "true";
}

bool Parser::IsFalse(const Token &token)
{
    return token.GetContent() == "false";
}

bool Parser::IsNull(const Token &token)
{
    return token.GetContent() == "null";
}

bool Parser::IsNumber(const Token &token)
{
    const string& content = token.GetContent();
    if(content.size() < 1)
    {
        return false;
    }
    char firstCharacter = token.GetContent().at(0);
    return (firstCharacter == '+' ||
            firstCharacter == '-' ||
            (firstCharacter >= '0' && firstCharacter <= '9'));
}

Value Parser::ReadValue()
{
    const Token& nextToken = PeekNonWhitespaceToken();

    if(IsStartOfString(nextToken))
    {
        return Value(ReadString());
    }
    else if(IsStartOfObject(nextToken))
    {
        return ReadObject();
    }
    else if(IsStartOfArray(nextToken))
    {
        return ReadArray();
    }
    else if(IsTrue(nextToken))
    {
        GetNextNonWhitespaceToken(); //skip
        return Value(true);
    }
    else if(IsFalse(nextToken))
    {
        GetNextNonWhitespaceToken(); //skip
        return Value(false);
    }
    else if(IsNull(nextToken))
    {
        GetNextNonWhitespaceToken(); //skip
        return Value();
    }
    else if(IsNumber(nextToken))
    {
        return ReadNumber();
    }

    errors.push_back(CreateErrorFromToken(nextToken, "Invalid syntax"));
    return Value();
}

Value Parser::ReadString()
{
    const Token& startToken = GetNextNonWhitespaceToken();
    const string& stringStart = startToken.GetContent();
    if(!IsStartOfString(startToken))
    {
        errors.push_back(CreateErrorFromToken(startToken, "Expected string opening"));
        return Value();
    }

    string result;
    bool stringCompleted = false;
    Token currentToken = GetNextToken();
    string currentTokenString = currentToken.GetContent();
    while(currentTokenString != "\n" || currentTokenString != "")
    {
        if(currentTokenString == stringStart)
        {
            stringCompleted = true;

            //de-encode the string.
            Utilities::ReplaceAll(result, "\\\"", "\"");
            Utilities::ReplaceAll(result, "\\\\", "\\");
            Utilities::ReplaceAll(result, "\\/", "/");
            Utilities::ReplaceAll(result, "\\b", "\b");
            Utilities::ReplaceAll(result, "\\f", "\f");
            Utilities::ReplaceAll(result, "\\n", "\n");
            Utilities::ReplaceAll(result, "\\r", "\r");
            Utilities::ReplaceAll(result, "\\t", "\t");
            break;
        }

        result += currentTokenString;

        currentToken = GetNextToken();
        currentTokenString = currentToken.GetContent();
    }

    if(!stringCompleted)
    {
        errors.push_back(CreateErrorFromToken(currentToken, "Expected string ending"));
        return Value();
    }

    return Value(result);
}

Value Parser::ReadObject()
{
    Token currentToken = GetNextNonWhitespaceToken();

    if(!IsStartOfObject(currentToken))
    {
        errors.push_back(CreateErrorFromToken(currentToken, "Expected \"{\""));
        return Value();
    }

    Value objectValue;
    while(true)
    {
        currentToken = PeekNonWhitespaceToken();

        if(objectValue.GetLength() > 0)
        {
            if(currentToken.GetContent() != ",")
            {
                if(currentToken.GetContent() != "}")
                {
                    errors.push_back(CreateErrorFromToken(currentToken, "Expecting end of object"));
                    return Value();
                }
                else
                {
                    GetNextNonWhitespaceToken(); //skip
                    break;
                }
            }
            else
            {
                GetNextNonWhitespaceToken(); //skip
            }
        }
        else
        {
            if(currentToken.GetContent() == "}")
            {
                //Empty Object
                GetNextNonWhitespaceToken(); //skip
                break;
            }
        }

        //Get a name.

        Value pairName = ReadString();
        if(pairName.GetValueType() == ValueType::Null)
        {
            errors.push_back(CreateErrorFromToken(currentToken, "Expected name of object"));
            return Value();
        }

        //Expect the pair seperator.
        currentToken = GetNextNonWhitespaceToken();
        if(currentToken.GetContent() != ":")
        {
            errors.push_back("Expected \":\"");
            return Value();
        }

        //Now get the pair value.
        Value pairValue = ReadValue();

        objectValue.SetValueForKey(pairName.ToString(), pairValue);
    }

    return objectValue;
}

Value Parser::ReadArray()
{
    Token currentToken = GetNextNonWhitespaceToken();

    if(!IsStartOfArray(currentToken))
    {
        errors.push_back(CreateErrorFromToken(currentToken, "Expected \"[\""));
        return Value();
    }

    Value arrayValue;


    while(true)
    {
        currentToken = PeekNonWhitespaceToken();

        if(arrayValue.GetLength() > 0)
        {
            //Expect comma.
            if(currentToken.GetContent() != ",")
            {
                //Otherwise, expect the end of the array.
                if(currentToken.GetContent() != "]")
                {
                    errors.push_back(CreateErrorFromToken(currentToken, "Expected end of array"));
                    return Value();
                }
                else
                {
                    SkipToken();
                    break;
                }
            }
            else
            {
                SkipToken();
            }
        }
        else
        {
            //Empty array.
            if(currentToken.GetContent() == "]")
            {
                SkipToken();
                break;
            }
        }

        arrayValue.Push(ReadValue());
    }

    return arrayValue;
}

Value Parser::ReadNumber()
{
    Token token = GetNextNonWhitespaceToken();
    const string& currentString = token.GetContent();

    int sign;
    size_t characterIndex = 0;
    bool signRead = true;

    if(currentString.at(0) == '-')
    {
        sign = -1;
        ++characterIndex;
    }
    else if(currentString.at(0) == '+')
    {
        sign = 1;
    }
    else
    {
        sign = 1;
        signRead = false;
    }

    int integerValue = 0;
    bool integerCharacterRead = false;
    char character=0;
    bool expectingExponent = false;

    while(true)
    {
        if(characterIndex >= currentString.size())
        {
            if(signRead && characterIndex <= 1)
            {
                //Throw stuff. only contains a sign.
                errors.push_back(CreateErrorFromToken(token, "Expecting number after sign"));
                break;
            }
            else
            {
                //Next stage
                break;
            }
        }
        else
        {
            character = currentString.at(characterIndex);
            ++characterIndex;
        }

        if(character >= '0' && character <= '9')
        {
            integerValue = integerValue * 10 + (character - '0');
            integerCharacterRead = true;
        }
        else if (character == 'e' || character == 'E')
        {
            expectingExponent = true;
            break; // to next stage.
        }
        else if (character == '.')
        {
            if(!integerCharacterRead)
            {
                errors.push_back(CreateErrorFromToken(token, "Invalid decimal, missing integer"));
                return Value();
                //You need an integer before the decimal THROW STUFF
            }
            break; //to next stage.
        }
        else
        {
            errors.push_back(CreateErrorFromToken(token, "Invalid character in number"));
            return Value();
        }
    }

    int decimalValue = 0;
    int decimalDigits = 0;

    if(character == '.')
    {
        while(true)
        {
            if(characterIndex >= currentString.size())
            {
                //To next stage. Shouldn't be expecting exponent.
                break;
            }
            else
            {
                character = currentString.at(characterIndex);
                ++characterIndex;
            }

            if(character >= '0' && character <= '9')
            {
                decimalValue = decimalValue * 10 + (character - '0');
                ++decimalDigits;
            }
            else if(character == 'e' || character == 'E')
            {
                expectingExponent = true;
                ++characterIndex;
                break; //to next stage.
            }
            else
            {
                //THROW STUFF
                errors.push_back(CreateErrorFromToken(token, "Invalid characters in decimal"));
                return Value();
            }
        }
    }

    int exponentValue = 0;
    int exponentSign = 1;

    if(expectingExponent)
    {
        bool exponentDefined = false;

        character = currentString.at(characterIndex);
        if(character == '+')
        {
            exponentSign = 1;
            ++characterIndex;
        }
        else if(character == '-')
        {
            exponentSign = -1;
            ++characterIndex;
        }
        else
        {
            exponentSign = 1;
        }

        while(true)
        {
            if(characterIndex >= currentString.size())
            {
                if(exponentDefined)
                {
                    break; //Done here.
                }
                else
                {
                    //Throw Exception.
                    errors.push_back(CreateErrorFromToken(token, "Incomplete exponent."));
                    return Value();
                }
            }
            else
            {
                character = currentString.at(characterIndex);
                ++characterIndex;
            }

            if(character >= '0' && character <= '9')
            {
                exponentValue = exponentValue * 10 + (character - '0');
                exponentDefined = true;
            }
            else
            {
                //THROW EXCEPTION.
                errors.push_back(CreateErrorFromToken(token, "Invalid characters in exponent."));
                return Value();
            }
        }
    }

    double result = (double)integerValue;

    double divedend = 1;
    for(int i = 0; i < decimalDigits; ++i)
    {
        divedend *= 10;
    }

    result += (double)decimalValue / divedend;

    if(expectingExponent)
    {
        result = result * pow(10, exponentValue * exponentSign);
    }

    result *= sign;

    return Value(result);
}

string Parser::CreateErrorFromToken(const Token &token, const string errorString)
{
    ostringstream stream;
    stream << "Line " << token.GetLine() << ", Column " << token.GetColumn() << ": " << errorString;
    return stream.str();
}
