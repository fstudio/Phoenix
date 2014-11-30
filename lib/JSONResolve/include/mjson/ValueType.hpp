#ifndef MJSON_VALUETYPE_HPP
#define MJSON_VALUETYPE_HPP

#include <string>
#include <map>

namespace mjson
{
    namespace ValueType
    {
        /**
         * @brief Defines possible JSON value types.
         */
        enum ValueType
        {
            Object,
            Array,
            Number,
            String,
            Boolean,
            Null
        };
    }

    extern const std::string& GetValueTypeName(ValueType::ValueType type);
}

#endif
