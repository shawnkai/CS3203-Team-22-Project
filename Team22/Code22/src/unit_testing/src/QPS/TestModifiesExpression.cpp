//
// Created by Tanishq Sharma on 7/3/23.
//


#include "QPS/QueryParser/QueryParser.h"
#include "catch.hpp"
#include "QPS/Exceptions/Exceptions.h"

using namespace std;

TEST_CASE("TestCase1_ParseSelectWithSuchThatModifies_ShouldSuccess") {
QueryParser queryParser;
string declaration = "variable v;";
string query = "Select v such that Modifies(1, v)";

queryParser.parse(declaration);

SelectExpression *actualResult = queryParser.parse(query);

REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase2_ParseSelectWithSuchThatModifiesWithWildCard_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "procedure p;";
    string query = "Select p such that Modifies(p, _)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase3_ParseSelectWithSuchThatModifiesWithArg1Ident_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "variable v; procedure p;";
    string query = "Select p such that Modifies(\"proc\", _)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase4_UndeclaredVariableArg1ModifiesPExpression_SemanticError") {
    QueryParser queryParser;

    string declaration = "variable v; read r;";
    string query = "Select v such that Modifies(a, v)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase5_UndeclaredNamedEntityArg2ModifiesSExpression_SemanticError") {
    QueryParser queryParser;

    string declaration = "variable v; read r;";
    string query = "Select v such that Modifies(r, a)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase6_UndeclaredNamedEntityArg2ModifiesPExpression_SemanticError") {
    QueryParser queryParser;

    string declaration = "variable v; read r;";
    string query = "Select v such that Modifies(v, a)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase7_UndeclaredNamedEntitySelectExpression_SemanticError") {
    QueryParser queryParser;

    string declaration = "variable v; read r;";
    string query = "Select x such that Modifies(v, a)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase8_ModifiesExpressionFirstArgPrint_SemanticError") {
    QueryParser queryParser;

    string declaration = "variable v; print p;";
    string query = "Select v such that Modifies(p, v)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase9_ModifiesExpressionSecondArgConstant_SemanticError") {
    QueryParser queryParser;

    string declaration = "variable v; read r; constant c;";
    string query = "Select v such that Modifies(r, c)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase10_ModifiesPExpressionSecondArgAssign_SemanticError") {
    QueryParser queryParser;

    string declaration = "variable v; read r; assign a;";
    string query = "Select v such that Modifies(r, a)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}
