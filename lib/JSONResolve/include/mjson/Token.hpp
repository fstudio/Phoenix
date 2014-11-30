#ifndef MJSON_TOKEN_HPP
#define MJSON_TOKEN_HPP

#include <string>

namespace mjson
{

    class Token
    {

        /**
         * @brief The line number this token starts at.
         */
        int line;

        /**
         * @brief The column number this token starts at.
         */
        int column;

        /**
         * @brief The content of this token itself.
         */
        std::string content;

        bool _containsWhitespace;

    public:

        Token();
        Token(int line, int column, const std::string& content);

        /**
         * @return The line number this token starts at.
         */
        int GetLine() const;

        /**
         * @return The column number this token starts at.
         */
        int GetColumn() const;

        /**
         * @return The content of this token.
         */
        const std::string& GetContent() const;

        bool ContainsWhitespace() const;

    };

}

#endif
