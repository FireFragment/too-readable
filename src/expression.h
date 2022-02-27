#ifndef TOOREADABLE_EXPRESSION_H
#define TOOREADABLE_EXPRESSION_H

#include <variant>
#include <vector>
#include "value.h"

namespace TooReadable {

/**
 * @brief Fully parsed TooReadable expression
 * 
 */
class Expression
{
public:
    enum Type {
        /**
         * @brief A literal
         * 
         */
        Literal,
        /**
         * @brief Variable or an arguent of parent function
         *
         */
        Variable
    };

    /**
     * @returns The type of expression.
     *
     * The type is deduced from type of `Value`, @see Value.
     */
    Type type();

    /**
     * @brief Calculate the value of expression
     *
     * @param[in] vars Values of variables and arguments present in current scope
     * @return Calculated value of the expression
     */
    Value evaluate(const std::vector<Value>* vars);

    Expression() {};
    /**
     * @brief Create `Expression` containing literal.
     *
     * @param val The value of the literal
     */
    Expression(Value val) : value(val) {};
    /**
     * @brief Create `Expression` containing variable.
     *
     * @param val The variable id
     */
    Expression(unsigned short int val) : value(val) {};
private:
    /**
     * @brief The value.
     *
     * The type of expression directly depends on type of this files
     * | Contains           | Is                   |
     * | ------------------ | -------------------- |
     * | Value              | Literal              |
     * | unsigned short int | Variable or argument |
     *
     * This conversion does the `type()` function.
     */
    std::variant<Value, unsigned short int> value;
};

}

#endif // TOOREADABLE_EXPRESSION_H
