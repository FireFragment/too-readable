#include <gtest/gtest.h>
#include "src/parse-states/unparsed.h"
#include "src/parse-states/divided.h"

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
