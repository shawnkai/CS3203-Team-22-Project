//
// Created by Tanishq Sharma on 27/3/23.
//

#include "QPS/Parser/Parser.h"
#include "catch.hpp"
#include "QPS/Exceptions/Exceptions.h"

using namespace std;

TEST_CASE("TestCase1_ParseSelectWithSuchThatCallsProcedures_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "procedure p1, p2;";
    string query = "Select p1 such that Calls(p1, p2)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase2_ParseSelectWithSuchThatCallsWildCard_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "procedure p;";
    string query = "Select p such that Calls(p, _)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase3_ParseSelectWithSuchThatCallsProcedureName_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "procedure p;";
    string query = "Select p such that Calls(p, \"Example\")";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase4_ParseSelectWithSuchThatCallsStmtType_SemanticException") {
    QueryParser queryParser;
    string declaration = "stmt s;";
    string query = "Select s such that Calls(s, _)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase5_ParseSelectWithSuchThatCallsProcedureNameWhitespaces_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "procedure p;";
    string query = "Select p such that Calls  (  p ,  \"  Example \"  )";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == "Select p such that Calls(p, \"Example\")");
}

TEST_CASE("TestCase6_ParseCallsProcedureUnknownCharacters_SyntacticException") {
    QueryParser queryParser;
    string declaration = "procedure p;";
    string query = "Select p such that Calls  (  p ,  \"  Example* \"  )";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}


TEST_CASE("TestCase7_ParseSelectWithSuchThatCallsStarProcedures_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "procedure p1, p2;";
    string query = "Select p1 such that Calls*(p1, p2)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase8_ParseSelectWithSuchThatCallsStarWildCard_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "procedure p;";
    string query = "Select p such that Calls*(p, _)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase9_ParseSelectWithSuchThatCallsStarProcedureName_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "procedure p;";
    string query = "Select p such that Calls*(\"Example\", p)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase10_ParseCallsStarProcedureNameWhitespaces_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "procedure p;";
    string query = "Select p such that Calls*  ( \"  Example \",  p)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == "Select p such that Calls*(\"Example\", p)");
}
