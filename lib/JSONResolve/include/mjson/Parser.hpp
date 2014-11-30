#ifndef MJSON_PARSER_HPP
#define MJSON_PARSER_HPP

#include <list>
#include <string>
#include <stack>
#include <mjson/Value.hpp>
#include "Token.hpp"

namespace mjson
{
    /**
     * @brief Parses JSON strings into values.
     */
    class Parser
    { 

        static Token emptyToken;

        std::list<Token>::iterator endTokenIterator;

        /**
         * @brief An iterator to the token currently being processed.
         */
        std::list<Token>::iterator currentTokenIterator;

        /**
         * @brief The list of errors encountered while processing tokens.
         */
        std::vector<std::string> errors;

        /**
         * @brief Splits a string into tokens based on a given delimiter.
         * @param The string to split.
         * @param The patern in the string to split by.
         * @param A vector to store the tokens in.
         */
        void Tokenize(const std::string& input, const std::string& delimiter, std::vector<std::string>& tokens);

        /**
         * @brief Returns the token pointed to by the current token iterator and increments the iterator.
         * @return The next token.
         */
        const Token& GetNextToken();

        const Token& GetNextNonWhitespaceToken();

        /**
         * @brief Returns the token pointed to by the current token iterator + 1. Doesn't increment the
         * current iterator.
         * @return The next token.
         */
        const Token& PeekToken();

        const Token& PeekNonWhitespaceToken();

        /**
         * @brief Increments the current token iterator.
         */
        void SkipToken();

        /**
         * @brief Checks if the contents of the given token could open a string.
         * @param token The token to check.
         * @return If the token could open a string or not.
         */
        bool IsStartOfString(const Token& token);

        /**
         * @brief Checks if the contents of the given token could open an array.
         * @param token The token to check.
         * @return If the token could open an array or not.
         */
        bool IsStartOfArray(const Token& token);

        /**
         * @brief Checks if the contents of the given token could open an object.
         * @param token The token to check.
         * @return If the token could open an object or not.
         */
        bool IsStartOfObject(const Token& token);

        /**
         * @brief Checks if the content of the token forms the true keyword.
         * @param token The token to check.
         * @return If the token is the true keyword.
         */
        bool IsTrue(const Token& token);

        /**
         * @brief Checks if the content of the token forms the false keyword.
         * @param token The token to check.
         * @return If the token is the false keyword.
         */
        bool IsFalse(const Token& token);

        /**
         * @brief Checks if the content of the token forms the null keyword.
         * @param token The token to check.
         * @return If the token is the null keyword.
         */
        bool IsNull(const Token& token);

        /**
         * @brief Checks if the first character of the token could start a number.
         * @param token The token to check.
         * @return Returns true if the token starts with +,-, or 0-9
         */
        bool IsNumber(const Token& token);

        /**
         * @brief Reads a string value from the tokens.
         * @return A value containing the string, a null value if the string
         * could not be read.
         */
        Value ReadString();

        /**
         * @brief Reads an object value from the tokens.
         * @return A value containing the object, or a null value if the object
         * could not be read.
         */
        Value ReadObject();

        /**
         * @brief Reads an array value from the tokens.
         * @return A value containing the array, or a null value if the array
         * could not be read.
         */
        Value ReadArray();

        /**
         * @brief Reads a number value from the tokens.
         * @return A value containing the number, or a null value if the number
         * could not be read.
         */
        Value ReadNumber();

        /**
         * @brief Reads a value from the tokens.
         * @return The read value, or a null value if the value could not be read.
         */
        Value ReadValue();

        /**
         * @brief Creates a detailed error message from a token.
         * @param token The token to use for line information.
         * @param errorString A string to use in the message.
         * @return The error message.
         */
        static std::string CreateErrorFromToken(const Token& token, const std::string errorString);

    public:

        /**
         * @brief Parses a JSON string into a value.
         * @param input The string to parse.
         * @param outValue Refrence to the value to store the parsed result. Value will be overwritten,
         * even if the parse fails.
         * @return If the string was sucessfully parsed.
         */
        bool Parse(const std::string& input, Value* outValue);

        /**
         * @brief Returns a list of errors from the previous parse. Will contain errors if a ParseException
         * was thrown when parsing.
         * @return The list of parse errors.
         */
        const std::vector<std::string>& GetErrors();

    };

}

#endif
