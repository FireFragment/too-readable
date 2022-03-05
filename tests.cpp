#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include "src/parse-states/unparsed.h"
#include "src/parse-states/divided.h"
#include "src/parse-states/parsed.h"
#include "src/ReadFile.h"
#include "src/builtinfunction.h"
#include "src/value.h"
#include "src/expression.h"

/**
 * \test Case, where it continues with string it should
 */
TEST ( unparsed_continueWith, true_case )
{
    TooReadable::ParseStates::Unparsed test = std::string("abcdef");
    EXPECT_EQ(test.ContinueWith("abc", false), "");
}

/**
 * \test Case, where it continues with string it shouldn't
 */
TEST ( unparsed_continueWith, false_case )
{
    TooReadable::ParseStates::Unparsed test = std::string("abcdef");
    EXPECT_EQ(test.ContinueWith("test", false), "abcd");
}

/**
 * \test Multiple cases.
 */
TEST ( unparsed_continueWith, multiple_cases )
{
    TooReadable::ParseStates::Unparsed test = std::string("abcdefghijk");
    EXPECT_EQ(test.ContinueWith("abc", false), "");
    EXPECT_EQ(test.ContinueWith("def", false), "");
    EXPECT_EQ(test.ContinueWith("test", false), "ghij");
}

/**
 * \test Multiple cases and instances of `Unparsed`.
 */
TEST ( unparsed_continueWith, multiple_cases_and_instances )
{
    TooReadable::ParseStates::Unparsed test1 = std::string("abcdefghijklmno");
    EXPECT_EQ(test1.ContinueWith("abc", false), "");
    EXPECT_EQ(test1.ContinueWith("def", false), "");
    TooReadable::ParseStates::Unparsed test2 = std::string("testing_str");
    EXPECT_EQ(test1.ContinueWith("ghi", false), "");
    EXPECT_EQ(test2.ContinueWith("test", false), "");
    EXPECT_EQ(test2.ContinueWith("Hello!", false), "ing_st");
    EXPECT_EQ(test1.ContinueWith("jk", false), "");
    EXPECT_EQ(test1.ContinueWith("end", false), "lmn");
}

/**
 * \test Make sure it doesn't break on false case.
 */
TEST ( unparsed_continueWith, true_case_after_false_case )
{
    TooReadable::ParseStates::Unparsed test = std::string("abcdefghijk");
    EXPECT_EQ(test.ContinueWith("abc", false), "");
    EXPECT_EQ(test.ContinueWith("def", false), "");
    EXPECT_EQ(test.ContinueWith("test", false), "ghij");
    EXPECT_EQ(test.ContinueWith("gh", false), "");
}

/**
 * \test continuesWith argument overhangs the string.
 */
TEST ( unparsed_continueWith, overhang )
{
    TooReadable::ParseStates::Unparsed test1 = std::string("abcd");
    EXPECT_EQ(test1.ContinueWith("super_test", false), "abcd");   
}

/**
 * \test continuesWith argument overhangs the string.
 */
TEST ( unparsed_continueWith, overhang_almost_true )
{
    TooReadable::ParseStates::Unparsed test1 = std::string("abcd");
    EXPECT_EQ(test1.ContinueWith("abcdef", false), "abcd");   
}

/**
 * \test continuesWith Ensure, that the Unparsed throws the exception, if the code does not continue with given string.
 */
TEST ( unparsed_continueWith, throw_exception )
{
    TooReadable::ParseStates::Unparsed test = std::string("abcdef");
    EXPECT_THROW({
        test.ContinueWith("test");
    }, TooReadable::ParseStates::Unparsed::ArgNotFoundException);   
}

/**
 * \test Test of `unparsed.skipTo`.
 */
TEST ( unparsed_skipTo, basic )
{
    TooReadable::ParseStates::Unparsed test1 = std::string("abcdefghijklmnopqrstuv");
    EXPECT_EQ(test1.SkipTo("de"), "abc");   
    EXPECT_EQ(test1.SkipTo("hi"), "fg");   
    EXPECT_EQ(test1.SkipTo("nopq"), "jklm");  
    EXPECT_THROW({
        test1.SkipTo("opq");
    }, TooReadable::ParseStates::Unparsed::ArgNotFoundException);   
    
    EXPECT_EQ(test1.SkipTo("uv"), "rst");  
}

/**
 * \test Test of `unparsed.skipTo` and `unparsed.continueWith`.
 */
TEST ( unparsed, skipTo_continueWith )
{
    TooReadable::ParseStates::Unparsed test1 = std::string("abcdefghijklmnopqrstuv");
    EXPECT_EQ(test1.SkipTo("de"), "abc");   
    EXPECT_EQ(test1.SkipTo("hi"), "fg");   
    EXPECT_EQ(test1.ContinueWith("jkl"), "");   
    EXPECT_THROW({
        test1.SkipTo("lmn");
    }, TooReadable::ParseStates::Unparsed::ArgNotFoundException);   
    
    EXPECT_EQ(test1.SkipTo("uv"), "mnopqrst");  
}

/**
 * \test Test of `expectEnd`, shouldn't throw anything.
 */
TEST ( unparsed_expectEnd, success) 
{
    TooReadable::ParseStates::Unparsed test1 = std::string("abcd");
    test1.SkipTo("cd");
    test1.ExpectEnd();
}

/**
 * \test Test of `expectEnd`, should throw.
 */
TEST ( unparsed_expectEnd, failture ) 
{
    TooReadable::ParseStates::Unparsed test1 = std::string("abcde");
    test1.SkipTo("cd");
    EXPECT_THROW(test1.ExpectEnd(), TooReadable::ParseStates::Unparsed::ExpectedEndException);
}

// Sample TOR program used across the tests
//const std::string sampleProgram = "Please run the sample program.\n\nHow to run the sample program\n=============================\n\n 1. Greet everything and everyone.\n     - Test argument 1: `Test`\n     - Second testing argument: `Another test`\n 2. Propagate TooReadable.\n\nHow to greet everything and everyone\n====================================\n\nWhat do we need to know\n-----------------------\n\nTo Greet everything and everyone, we need to also know theese values:\n - Test argument 1\n - Second testing argument\n\nInstructions\n------------\n\n 1. Greet the world.\n 2. Greet the user.\n";

const std::string sampleProgram() {
    std::ifstream inFile("test_code/testing_code.tor");
    return ReadFile(inFile);
}

/**
 * \test divided Test creating \c TooReadable::ParseStates::Divided class from \c sampleProgram.
 */
TEST ( divided, program )
{
    TooReadable::ParseStates::Divided test1;
    try {
        test1 = TooReadable::ParseStates::Unparsed(sampleProgram());
    } catch (TooReadable::ParseStates::Unparsed::ArgNotFoundException err) {
        std::cout << err.what();
    }
    EXPECT_EQ(test1.mainFunc, "Run the sample program");
    
    // ----- Run the sample program -----
    EXPECT_EQ(test1.functions[0].name, "Run the sample program");
    EXPECT_EQ(test1.functions[0].steps[0].funcName, "Greet everything and everyone");
    EXPECT_EQ(test1.functions[0].steps[0].parentFunc, test1.functions[0].name);
    EXPECT_EQ(test1.functions[0].steps[1].funcName, "Propagate TooReadable");
    EXPECT_EQ(test1.functions[0].steps[1].parentFunc, test1.functions[0].name);
    
    // In the testing program, arguments are listed in wrong order (it should be allowed)
    // Arguments are put to correct order in constructor of `Parsed`.
    EXPECT_EQ(test1.functions[0].steps[0].outOfLineArgs[0].name, "Second testing argument"); 
    EXPECT_EQ(test1.functions[0].steps[0].outOfLineArgs[0].value, "`Another test`"); 
    EXPECT_EQ(test1.functions[0].steps[0].outOfLineArgs[1].name, "Test argument 1"); 
    EXPECT_EQ(test1.functions[0].steps[0].outOfLineArgs[1].value, "`Test`"); 
    
    EXPECT_EQ(test1.functions[0].outOfLineArgs.size(), 0);
    
    // ----- Greet everything and everyone -----
    EXPECT_EQ(test1.functions[1].name, "Greet everything and everyone");
    EXPECT_EQ(test1.functions[1].steps[0].funcName, "Greet the world");
    EXPECT_EQ(test1.functions[1].steps[1].funcName, "Greet the user");
    
    EXPECT_EQ(test1.functions[1].outOfLineArgs, std::vector<std::string>({ "Test argument 1", "Second testing argument" }));
}

/**
 * \test parsed_constructor Test parsing \c sampleProgram.
 */
TEST ( parsed_constructor, program )
{
    TooReadable::ParseStates::Parsed test1 = TooReadable::ParseStates::Divided(TooReadable::ParseStates::Unparsed(sampleProgram()));
    EXPECT_EQ(test1.mainFunc, test1.funcs[0]); // The main function is correct
    
    // Check names of functions
    EXPECT_EQ(test1.funcs[0]->name, "Run the sample program");
    EXPECT_EQ(test1.funcs[1]->name, "Greet everything and everyone");
    
    // Check bodies of functions
    EXPECT_EQ(test1.funcs[0]->body[0].toCall, test1.funcs[1]);
    EXPECT_EQ(test1.funcs[0]->body[1].toCall->name, "Propagate TooReadable");
    EXPECT_EQ(test1.funcs[1]->body[0].toCall->name, "Greet the world");
    EXPECT_EQ(test1.funcs[1]->body[1].toCall->name, "Greet the user");
    
    EXPECT_EQ(std::string(test1.funcs[0]->body[0].args[0]), "Test");
    EXPECT_EQ(std::string(test1.funcs[0]->body[0].args[1]), "Another test");
}

/**
 * \test overall Testing, that parsing programs, that shouldn't be parsed (eg. syntax errors) throws an error.
 */
TEST ( overall, failtures ) {
    std::string pathToFailing = "./test_code/parsing_fails"; // Directory with invalid code sample. 
    for (const auto & entry : std::filesystem::directory_iterator(pathToFailing)) { // For each file in `test_code/parsing_fails`
        
        std::cout << "TESTING: " <<  entry.path() << std::endl;
        std::ifstream inputFile = std::ifstream ( entry.path() ); // Read the file with invalid code.
        
        EXPECT_ANY_THROW({ // The programs should not be parsed.
            // Try to parse the code
            TooReadable::ParseStates::Unparsed code = ReadFile ( inputFile );
            TooReadable::ParseStates::Divided dividedCode = code;
            TooReadable::ParseStates::Parsed parsedCode = dividedCode;
        });

    }
}

/**
 * \test builtin_funcs Ensure, that all builtin functions doesn't throw anything.
 */
// TODO: Uncomment and fix
// TEST ( builtin_funcs, not_crashing ) {
//     for (TooReadable::BuiltinFunction* func : TooReadable::BuiltinFuncs::list)
//         func->run();
// }

/**
 * @test value Ensure, that conversion of `Value` to `bool` and `bool` to `Value` is done properly.
 */
TEST( value, bool_cast ) {
    TooReadable::Value t;
    t = true;
    EXPECT_TRUE(t);
    t = false;
    std::cout << std::string(t) << '\n';
    EXPECT_FALSE(t);
    
    t = "YES"; EXPECT_TRUE(t);
    t = "Yes"; EXPECT_TRUE(t);
    t = "yes"; EXPECT_TRUE(t);
    
    t = "NO"; EXPECT_FALSE(t);
    t = "No"; EXPECT_FALSE(t);
    t = "no"; EXPECT_FALSE(t);
    
    t = "Hello world";
    EXPECT_THROW(
        bool aa = t,
        TooReadable::Value::InvalidBoolConv
    );
}

/**
 * @test value Ensure, that conversion of `Value` to `int` and `int` to `Value` is done properly.
 */
TEST( value, int_cast ) {
    TooReadable::Value t;
    t = 123;
    EXPECT_EQ(t, 123);
    EXPECT_EQ(std::string(t), "123");
    
    t = "-137";
    EXPECT_EQ(t, -137);
    EXPECT_EQ(std::string(t), "-137");
}

/**
 * @test value Ensure, that conversion of literal to `Value` works properly
 */
TEST( value, from_literal ) {
    TooReadable::Value t = TooReadable::Value::FromLiteral("12");
    EXPECT_EQ(t, 12);

    t = TooReadable::Value::FromLiteral("`My text`");
    EXPECT_EQ((std::string)t, "My text");

    EXPECT_THROW({
        t = TooReadable::Value::FromLiteral("Haha invalid literal");
    }, TooReadable::Value::BadLiteral);

    t = "-137";
    EXPECT_EQ(t, -137);
    EXPECT_EQ(std::string(t), "-137");
}

/**
 * @test expression Test if saving and reading literals from expressions works
 *
 */
TEST( expression, literal ) {
    TooReadable::Expression e = TooReadable::Value("aa");
    EXPECT_EQ(e.type(), TooReadable::Expression::Literal);
    EXPECT_EQ((std::string)e.evaluate({}), "aa");
}


/**
 * @test expression Test if saving and reading variables from expressions works
 *
 */
TEST( expression, variable ) {
    TooReadable::Expression e = 3;
    std::vector<TooReadable::Value> vars = {123, 45, 887, 778, 56};
    EXPECT_EQ(e.type(), TooReadable::Expression::Variable);
    EXPECT_EQ(e.evaluate(&vars), 778);
}

/**
 * @test expression Test if parsing expressions works
 *
 */
TEST( expression, parse ) {
    std::vector<std::string> varNames = {"My first variable", "Some second variable"};
    std::vector<TooReadable::Value> vars = {123, 45};

    TooReadable::Expression e = TooReadable::Expression::Parse("`Hello world`", varNames);
    EXPECT_EQ(e.type(), TooReadable::Expression::Literal);
    EXPECT_EQ((std::string)e.evaluate(&vars), "Hello world");
}
