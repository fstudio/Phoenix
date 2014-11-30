#ifndef MJSON_UTILITIES_HPP
#define MJSON_UTILITIES_HPP

#include <string>
#include <vector>

namespace mjson
{
    class Utilities
    {

    public:

        /**
         * @brief Trims all whitespace on the left side of the given string.
         * This function comes from http://stackoverflow.com/a/217605/594760
         * @param in The string to trim.
         * @return A refrence to the passed string.
         */
        static std::string &TrimLeft(std::string &in);

        /**
         * @brief Trims all whitespace on the right side of the given string.
         * This function comes from http://stackoverflow.com/a/217605/594760
         * @param in The string to trim.
         * @return A refrence to the passed string.
         */
        static std::string &TrimRight(std::string &in);

        /**
         * @brief Trims all whitespace on both sides of the given string.
         * This function comes from http://stackoverflow.com/a/217605/594760
         * @param in The string to trim.
         * @return A refrence to the passed string.
         */
        static std::string &Trim(std::string &in);

        static void SplitWhitespace(const std::string& in, std::vector<std::string> &strings);

        static void ReplaceAll(std::string& in, const std::string& token, const std::string& newToken);
    };

}

#endif
