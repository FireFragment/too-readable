#pragma once

#include <string>
#include <vector>
#include "unparsed.h"

namespace TooReadable::ParseStates {

/** \class Divided divided.h "parse-states/divided.h"
 *  \brief **First stage of parsing:** divided to basic parts.
 */
class Divided
{
public:
    /**
     * @brief Thrown when step has lowercase letter at the beggining
     *
     */
    class LowLetterAtBegginingOfStep : public Exception {
    public:
        LowLetterAtBegginingOfStep(std::string funcName): funcName(funcName) {};

        std::string funcName;
        const std::string what() override {
            return "Sentences starts with capital letter, but you wrote `" + funcName + "`, which starts with lowercase letter.\nTry changing it to `" + (char)toupper(funcName[0]) + funcName.substr(1) + "`";
        };
    };

    /**
     * \brief \c Function call
     */
    class Step {
    public:
        Step(std::string funcName, std::string parentFunc) : funcName(funcName), parentFunc(parentFunc) {};

        /**
         * @brief Parse TOR code and generate `Divided::Step`
         *
         * @param code Code, that is currently at the line that represents the step, but after this line's indentation eg.
         *             ```cpp
         *             Add two numbers.
         *                  - First number: 10
         *                  - Second number: 42
         *             ```
         *             First line shouldn't be indented nor preceeded by step number, whereas argument list should be intended as in code.
         *             If it's condition, conditional function call should be included and indented as in code (intended with 4 spaces).
         * @param enforceCapital If true, throws exception when function name isn't capitalized.
         * @return The divided step
         */
        static Step fromCode(Unparsed* code, std::string _parentFunc, bool enforceCapital = true);

        bool operator== (Step rhs) const {
            return (rhs.funcName == funcName) && (rhs.outOfLineArgs == outOfLineArgs) && (rhs.parentFunc == parentFunc);
        };
        /**
         * @brief Out-of-line argument assignment when calling function
         */
        class OutOfLineArgument {
        public:
            bool operator== (OutOfLineArgument rhs) const {
                return (rhs.name == name) && (rhs.value == value);
            };
            /**
             * @brief The name of the argument
             */
            std::string name;
            /**
             * @brief The assigned value
             * 
             * In format of unparsed expression
             */
            std::string value;
        };
        
        /**
         * @brief The name of the called function
         */
        std::string funcName;
        
        /**
         * @brief The name of the parent function
         * 
         * The step is part of body of this function 
         */
        std::string parentFunc;
        
        /**
         * @brief Out-of-line arguments passed to the function
         */
        std::vector<OutOfLineArgument> outOfLineArgs;

        /**
         * @brief If this step is condition, this is the command ran, if the condition fullfiled
         *
         * If it's `NULL`, this step is not condition, @see ::isCondition.
         */
        Step* conditionalCommand = NULL;

        /**
         * @brief If this step is condition, this is the command ran, if the condition isn't fullfiled
         */
        Step* elseCommand = NULL;

        /**
         * @brief Check, whether this step is condition
         *
         * @return True, if the step is condition, false if it isn't
         */
        inline bool isCondition() const {
            return conditionalCommand == NULL;
        }

        Step(const Step& original) {
            outOfLineArgs = original.outOfLineArgs;
            parentFunc = original.parentFunc;
            funcName = original.funcName;
            if (original.conditionalCommand != NULL)
                conditionalCommand = new Step(*original.conditionalCommand);

            if (original.elseCommand != NULL)
                elseCommand = new Step(*original.elseCommand);
        }

        ~Step() {
            if (conditionalCommand != NULL)
                delete conditionalCommand;
        }
    };
    
    /**
     * \brief Function of TOR program.
     */
    class Function {
    public:
        
        Function(
            const std::string name,
            std::vector<Step> steps
        ):name(name), steps(steps) {};
        Function() {};

        bool operator== (Function rhs) const {
            return (rhs.name == name) && (rhs.steps == steps);
        };
        
        /**
         * @brief Out-of-line arguments of the function
         * 
         * Out-of-line arguments are assigned in function call this way:
         * ~~~~{.tor}
         * 1. Do something
         *     - Inline argument 1: "Value of the argument"
         *     - Inline argument 2: "Value of the second argument"
         * ~~~~
         * 
         * Out-of-line arguments are defined in function definition this way:
         * ~~~~{.tor}
         * How to do something
         * ===================
         * 
         * What do we need to know
         * -----------------------
         * 
         * To do something, we need to also know theese values:
         * 
         *  - Inline argument 1
         *  - Inline argument 2
         * 
         * Instructions
         * ------------
         * 
         *  1. Here is the function body
         *  2. Second step
         * ~~~~
         */
        std::vector<std::string> outOfLineArgs;

        /**
         * \brief Name of the function.
         */
        std::string name;
        /**
         * \brief Steps of the function.
         */
        std::vector<Step> steps;
    };
    
    /**
     * Default constructor
     */
    Divided() {}
    /**
     * \brief Divides \c original to this class.
     * \param[in] original The program to parse.
     */
    Divided(Unparsed original);
    
    /**
     * \brief The main function of the program.
     * 
     * Empty string means, that program is a library hasn't main function;
     */
    std::string mainFunc;
    
    /**
     * \brief Functions of the program.
     */
    std::vector<Function> functions;
};

}
