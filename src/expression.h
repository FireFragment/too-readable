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
        Variable,
        /**
         * @brief Return value of another step
         *
         */
        ReturnValue
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
     * @param[in] vars       Values of variables and arguments present in current scope
     * @param[in] returnVals Values returned from previously done steps.
     *                       Index 0 should correspond to return value of first step.
     * @return Calculated value of the expression
     */
    Value evaluate(const std::vector<Value>* vars, const std::vector<Value>* returnVals);

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
     * @param isReturn Set to true, if the type is return value of another step
     */
    Expression(unsigned short int val, bool isReturn) : value(val), isReturn(isReturn) {};

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
     * | Contains  | Is                                                        |
     * | --------- | --------------------------------------------------------- |
     * | Value     | Literal                                                   |
     * | short int | Variable, argument or return value of another step        |
     *
     * This conversion does the `type()` function.
     */
    std::variant<Value, short int> value;

    /**
     * @brief True, if the type is return value of another step
     *
     * Means something, only if `value` contains `short int`
     */
    bool isReturn = false;
};

}

#endif // TOOREADABLE_EXPRESSION_H
