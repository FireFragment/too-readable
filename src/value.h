#pragma once

#include <string>
#include "exception.h"

namespace TooReadable {

/**
 * \brief **Value used in TOR program** as arguments, return values, value of variables, etc.
 */
class Value {
public:
    
    /**
     * @brief Thrown, when conversion of `Value` to `bool` failed, because it wasn't convertable to `bool`.
     */
    class InvalidBoolConv : public Exception {
    public:
        using Exception::Exception;
        
        /**
         * @param[in] badVal The value, user attempted to convert to `bool`.
         */
        InvalidBoolConv(std::string badVal) : badVal(badVal) {};
        
        /**
         * @brief The value, user attempted to convert to `bool`.
         */
        std::string badVal;
        
        const std::string what();
    };
    
    // Casts
    operator std::string() const { return val; }
    operator int()         const { return std::stoi(val); } // TODO: Throw exception when `val` isn't number
    /**
     * @brief Converts the value to `bool`
     * 
     * Conversion table:
     * 
     * | Value | Result  |
     * | ----: | :------ |
     * |   yes | `true`  |
     * |   Yes | `true`  |
     * |   YES | `true`  |
     * |    no | `false` |
     * |    No | `false` |
     * |    NO | `false` |
     *
     * Converting any other value will throw `InvalidBoolConv`.
     */
    operator bool() const;
    
    Value(const std::string _val) { val = _val; };
    Value(const char* _val) { val = _val; };
    Value(const int _val) { val = std::to_string(_val); };
    Value(const bool _val);
    Value() {};
    
    /**
     * @brief Creates `Value` from literal. Alternative constructor.
     * 
     * Literal can be 
     *  - String wrapped in \` characters (eg. `\`Hello world\` `)
     *  - Number
     * 
     * TODO: Add booleans
     * 
     * @param literal The literal
     * @return TooReadable::Value
     */
    static Value FromLiteral(std::string literal);
protected:
    /**
     * @brief The actual value
     */
    std::string val;
};
}
