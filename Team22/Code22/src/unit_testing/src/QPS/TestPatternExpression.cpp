//
// Created by Tanishq Sharma on 7/3/23.
//

#include "QPS/Parser/Parser.h"
#include "catch.hpp"
#include "QPS/Exceptions/Exceptions.h"

using namespace std;

//Missing quotation marks, wildcard combinations
TEST_CASE("TestCase16_ParseSelectWithExactMatchingPattern_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a;";
    string query = R"(Select a pattern a(_, "x+y"))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(_, +xy))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase17_ParseSelectWithWildCardPattern_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a;";
    string query = R"(Select a pattern a(_, _"x+y"_))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(_, _+xy_))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase27_MissingOpeningQuoteWithoutWildcardsPatternExpression_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v pattern a(v, x+y\")";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase28_MissingClosingQuotePatternWithoutWildcardsExpression_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v pattern a(v, \"x+y)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase29_MissingClosingWildcardWithValidQuotesPatternExpression_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v pattern a(v, _\"x+y\")";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase30_MissingOpeningQuoteWithValidWildcardsPatternExpression_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v pattern a(v, \"x+y\"_)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase31_MissingAllQuotesWithNoWildcardPatternExpression_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v pattern a(v, x+y)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase32_MissingAllQuotesWithValidWildcardPatternExpression_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v pattern a(v, _x+y_)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase40_InvalidSymbolsExpressionSpecPatternExpression_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v pattern a(v, \"__\")";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase41_SuchThatPatternExpression_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = R"(Select a such that pattern a(_, "x+y"))";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}


//whitespace tests
TEST_CASE("TestCase42_WhitespaceOnLeftSideArg1PatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = R"(Select a pattern a( _, "x+y"))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(_, +xy))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase43_WhitespaceOnRightSideArg1PatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = R"(Select a pattern a(v  , "x+y"))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(v, +xy))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase44_MultipleWhitespaceOnBothSidesBothArgsPatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v pattern a(    v  ,   \"x+y\"  )";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select v such that pattern a(v, +xy))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase45_NoWhitespaceBothArgsPatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = R"(Select a pattern a(_,"x+y"))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(_, +xy))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase46_OneWhitespacesAfterSynAssignPatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = R"(Select a pattern a ( _ , "x+y"))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(_, +xy))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase47_MultipleWhitespacesAfterSynAssignPatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = R"(Select a pattern a  ( _ ,  "x+y"  ))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(_, +xy))";

    REQUIRE(actualResult->toString() == expected);
}


TEST_CASE("TestCase49_SuchThatPatternExpression_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = R"(Select a such that pattern a(_, "x+y"))";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

//whitespace tests
TEST_CASE("TestCase50_WhitespaceOnLeftSideArg1PatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = R"(Select a pattern a( _, "x+y"))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(_, +xy))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase51_WhitespaceOnRightSideArg1PatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = R"(Select a pattern a(v  , "x+y"))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(v, +xy))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase52_MultipleWhitespaceOnBothSidesBothArgsPatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v pattern a(    v  ,   \"x+y\"  )";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select v such that pattern a(v, +xy))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase53_NoWhitespaceBothArgsPatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = R"(Select a pattern a(_,"x+y"))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(_, +xy))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase54_OneWhitespacesAfterSynAssignPatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = R"(Select a pattern a ( _ , "x+y"))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(_, +xy))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase55_MultipleWhitespacesAfterSynAssignPatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = R"(Select a pattern a  ( _ ,  "x+y"  ))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(_, +xy))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase10_MultipleWhitespacesAfterSynAssignPatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "assign a;";
    string query = R"(Select a pattern a (_ , _"1 "_))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(_, _1_))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase10_SingleIntWithWhitespacePatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "assign a;";
    string query = R"(Select a pattern a (_ , _"1 "_))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(_, _1_))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase10_InvalidInfixExpressionPatternExpression_SyntacticException") {
    QueryParser queryParser;

    string declaration = "assign a;";
    string query = R"(Select a pattern a (_ , _" +temp"_))";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

