#include <mjson/Token.hpp>

using namespace mjson;
using namespace std;

Token::Token()
{

}

Token::Token(int line, int column, const std::string& content)
{
    this->line = line;
    this->column = column;
    this->content = content;
    _containsWhitespace = (content.size() > 0 && isspace(content.at(0)));
}

int Token::GetLine() const
{
    return line;
}

int Token::GetColumn() const
{
    return column;
}

const string& Token::GetContent() const
{
    return content;
}

bool Token::ContainsWhitespace() const
{
    return _containsWhitespace;
}

