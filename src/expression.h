#ifndef TOOREADABLE_EXPRESSION_H
#define TOOREADABLE_EXPRESSION_H

#include <variant>
#include <vector>
#include "value.h"

namespace TooReadable {

/**
 * @brief Fully parsed TooReadable expression
 * 
 * Expressions in TooReadable are very simple - it can be just reading variable or literal, nothing else.
 * No operators, no function calls and using their return value.
 *
 * TODO: Support `Value we've got from previous step`
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

    /**
     * @brief Parse given expression
     *
     * @param code The expression in the code to be parsed
     * @param vars Variable names in current scope ordered by ID
     * @return     The parsed expression
     */
    static Expression Parse(std::string code, std::vector<std::string> vars);

    struct InvalidExpression : Exception {
        /**
         * @brief The code causing the problem
         *
         */
        std::string TheExpression;

        InvalidExpression(std::string TheExpression) : TheExpression(TheExpression) {};

        const std::string what() {
            return "I don't know what is " + TheExpression + ".\nIf it's some concrete text wrap it in `s, so it would become `" + TheExpression + "`";
        };
    };
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
