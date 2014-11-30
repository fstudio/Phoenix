#include <mjson/Utilities.hpp>

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

using namespace mjson;
using namespace std;

string& Utilities::TrimLeft(string &in)
{
        in.erase(in.begin(), find_if(in.begin(), in.end(), not1(ptr_fun<int, int>(isspace))));
        return in;
}

string& Utilities::TrimRight(string &in)
{
        in.erase(find_if(in.rbegin(), in.rend(), not1(ptr_fun<int, int>(isspace))).base(), in.end());
        return in;
}

string& Utilities::Trim(string &in)
{
        return TrimLeft(TrimRight(in));
}

void Utilities::SplitWhitespace(const string &in, std::vector<string>& strings)
{
    if(in.size() < 1)
    {
        return;
    }

    size_t currentTokenStart = 0;
    bool lastCharWasWhitespace = isspace(in.at(0));
    for(size_t currentPosition = 0, count = in.size(); currentPosition < count; ++currentPosition)
    {
        char currentChar = in.at(currentPosition);
        bool charIsWhitespace = isspace(currentChar);
        if(charIsWhitespace != lastCharWasWhitespace)
        {
            strings.push_back(in.substr(currentTokenStart, currentPosition - currentTokenStart));
            currentTokenStart = currentPosition;

            lastCharWasWhitespace = charIsWhitespace;
        }

        if(currentPosition == count - 1)
        {
            strings.push_back(in.substr(currentTokenStart, (currentPosition - currentTokenStart) + 1));
        }
    }

}

void Utilities::ReplaceAll(string &in, const string &token, const string &newToken)
{
    size_t currentPosition = 0;
    size_t tokenLength = token.size();
    size_t newTokenLength = newToken.size();
    size_t tokenOffset = (newTokenLength - tokenLength) + 1;
    for(;;)
    {
        currentPosition = in.find(token, currentPosition);
        if(currentPosition == string::npos)
        {
            break;
        }
        in.replace(currentPosition, tokenLength, newToken, 0, newTokenLength);
        currentPosition += tokenOffset;
    }
}
