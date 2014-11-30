#ifndef MJSON_VALUE_HPP
#define MJSON_VALUE_HPP

#include <string>
#include <vector>
#include <map>
#include <mjson/ValueType.hpp>

namespace mjson
{
    /**
     * @brief Represents JSON datatypes.
     */
    class Value
    {
        typedef std::vector<Value> ArrayContainer;
        typedef std::map<std::string, Value> ObjectContainer;

        ArrayContainer arrayValues;
        ObjectContainer objectValues;

        std::vector<std::string> objectKeys;

        ValueType::ValueType type;

        double number;

        std::string stringValue;

        bool boolean;

        /**
         * @brief A static value used to return a null value.
         */
        static Value nullValue;

        static std::string emptyString;

        std::string ObjectValueToString() const;

        std::string ArrayValueToString() const;

        std::string NumberValueToString() const;

        std::string BooleanValueToString() const;

        std::string StringValueToJSONString() const;

        static std::string AsValidJSONString(const std::string& in);

        std::string CreateTypeMismatchString(const std::vector<ValueType::ValueType>& expected, ValueType::ValueType got);

    public:

        /**
         * @brief Initializes a null typed Value.
         */
        Value();

        /**
         * @brief Initializes a number typed Value from a double.
         * @param The number value.
         */
        Value(double number);

        /**
         * @brief Initializes a number typed Value from a float.
         * @param The number value.
         */
        Value(float number);

        /**
         * @brief Initializes a number typed Value from an integer.
         * @param The number value.
         */
        Value(int number);

        /**
         * @brief Initializes a string typed value.
         * @param The string value.
         */
        Value(const std::string& string);

        /**
         * @brief Initializes a string typed value with a c-string.
         * @param The c-string.
         */
        Value(const char* string);

        /**
         * @brief Initializes a boolean typed value.
         * @param The boolean value.
         */
        Value(bool boolean);

        /**
         * @brief Gets the json data type this value holds.
         * @return The type of this value.
         */
        ValueType::ValueType GetValueType() const;

        /**
         * @brief Gets the value with the given key, assuming this value is an object.
         * Throws TypeMismatchException if this value is not an object type.
         * Throws InvalidKeyException if the given key does not exist in the object.
         * @param key The key used to look up the value.
         * @return The value matching the given key.
         */
        const Value& GetWithKey(const std::string& key) const;

        /**
         * @brief Gets the value with the given index, assuming this value is an array.
         * Throws TypeMismatchException if this value is not an array type.
         * Throws OutOfRangeException if the given index is less than zero or greater than
         * the array length.
         * @param index
         * @return
         */
        const Value& GetAtIndex(int index) const;

        /**
         * @brief Returns the key at the given index
         * @param The index of the key to retrieve.
         * @return The key.
         */
        const std::string& GetKey(int index) const;

        /**
         * @brief Checks if the given key exists, assuming this value is an object.
         * Returns 0 if this value is not an object.
         * @param key The key to check.
         * @return If the key exists in the object. Returns false if the value is null.
         */
        bool ContainsKey(const std::string& key);

        /**
         * @brief Returns the ammount of values held by this value, assuming this value is an
         * array or an object.
         * @return The ammount of values held by this object or array. Returns 0 if the value is
         * not an array or an object.
         */
        int GetLength() const;

        /**
         * @brief Returns the value as a double.
         * @return The value as a double. Returns 0 if the value is not a number.
         */
        double ToDouble() const;

        /**
         * @brief Returns the value as a float.
         * @return The value as a float. Returns 0 if the value is not a number.
         */
        float ToFloat() const;

        /**
         * @brief Returns the value as an integer.
         * @return The value as an integer. Returns 0 if the value is not a number.
         */
        int ToInt() const;

        /**
         * @brief Returns this value as a string.
         * @return The value as a string. Returns an empty string if the value is not a string.
         */
        std::string ToString() const;

        /**
         * @brief Returns this value as a boolean. Returns false if the value is not a boolean.
         * @return The value as a boolean.
         */
        bool ToBoolean() const;

        /**
         * @brief Adds an element to this value, assuming it is an Array. If this value is
         * null typed, this value is converted into an array typed value.
         * Throws TypeMismatchException if this value is not an array or null type.
         * @param value The value to add the the array.
         */
        bool Push(const Value& value);

        /**
         * @brief Sets the value of a key, assuming this value is an Object. If this value is
         * null typed, this value is converted into an object typed value.
         * Throws TypeMismatchException if this value is not an object or null type.
         * @param key The key name to set.
         * @param value The value to set for the key.
         */
        bool SetValueForKey(const std::string& key, const Value& value);

        /**
         * @brief Returns the value as a JSON formatted string.
         * @return The JSON string representing this value.
         */
        std::string ToJSONString() const;
    };

}

#endif
