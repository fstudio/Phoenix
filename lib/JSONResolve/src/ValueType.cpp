#include <mjson/ValueType.hpp>

namespace mjson
{
    class ValueTypeNameManager
    {
        std::map<ValueType::ValueType, std::string> typemap;

    public:
        ValueTypeNameManager()
        {
            typemap.insert(std::make_pair(ValueType::Array, "Array"));
            typemap.insert(std::make_pair(ValueType::Boolean, "Boolean"));
            typemap.insert(std::make_pair(ValueType::Null, "Null"));
            typemap.insert(std::make_pair(ValueType::Number, "Number"));
            typemap.insert(std::make_pair(ValueType::Object, "Object"));
            typemap.insert(std::make_pair(ValueType::String, "String"));
        }

        const std::string& GetName(ValueType::ValueType value) const
        {
            return typemap.at(value);
        }
    };
}

const mjson::ValueTypeNameManager valueTypeNameManager;

const std::string& mjson::GetValueTypeName(ValueType::ValueType type)
{
    return valueTypeNameManager.GetName(type);
}
