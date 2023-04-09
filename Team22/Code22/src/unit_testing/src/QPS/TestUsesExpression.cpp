//
// Created by Tanishq Sharma on 7/3/23.
//

#include "QPS/QueryParser/QueryParser.h"
#include "catch.hpp"
#include "QPS/Exceptions/Exceptions.h"

using namespace std;

TEST_CASE("TestCase1_ParseSelectWithSuchThatUses_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "variable v;";
    string query = "Select v such that Uses(1, v)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase2_ParseSelectWithSuchThatUsesWithIdent_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "variable v; procedure p;";
    string query = "Select p such that Uses(p, \"x\")";

    queryParser.parse(declaration);
    SelectExpression *actualResult = queryParser.parse(query);
    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase3_ParseSelectWithSuchThatUsesWithWildCard_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "variable v; procedure p;";
    string query = "Select p such that Uses(p, _)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase4_ParseSelectWithSuchThatUsesWithArg1Ident_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "variable v; procedure p;";
    string query = "Select p such that Uses(\"proc\", _)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase5_UndeclaredNamedEntityArg2UsesSExpression_SemanticError") {
QueryParser queryParser;

string declaration = "variable v; print p;";
string query = "Select v such that Uses(p, a)";

queryParser.parse(declaration);

bool throwsException = false;

try {
Expression *exp1 = queryParser.parse(query);
} catch (SemanticException& e) {
throwsException = true;
}

REQUIRE(throwsException);
}

TEST_CASE("TestCase6_UndeclaredNamedEntityArg2UsesPExpression_SemanticError") {
QueryParser queryParser;

string declaration = "variable v; read r;";
string query = "Select v such that Uses(v, a)";

queryParser.parse(declaration);

bool throwsException = false;

try {
Expression *exp1 = queryParser.parse(query);
} catch (SemanticException& e) {
throwsException = true;
}

REQUIRE(throwsException);
}


//first arg for uses/modifies cannot be wildcard

TEST_CASE("TestCase7_ModifiesExpressionFirstArgWildcard_SemanticError") {
    QueryParser queryParser;

    string declaration = "variable v; read r;";
    string query = "Select v such that Modifies(_, v)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase8_UsesExpressionFirstArgWildcard_SemanticError") {
    QueryParser queryParser;

    string declaration = "variable v; read r;";
    string query = "Select v such that Uses(_, v)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase9_UsesExpressionFirstArgRead_SemanticError") {
    QueryParser queryParser;

    string declaration = "variable v; read r;";
    string query = "Select v such that Uses(r, v)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase10_UsesSExpressionSecondArgConstant_SemanticError") {
    QueryParser queryParser;

    string declaration = "variable v; print p; constant c;";
    string query = "Select v such that Uses(p, c)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase11_UsesPExpressionSecondArgAssign_SemanticError") {
    QueryParser queryParser;

    string declaration = "variable v; read r; assign a;";
    string query = "Select v such that Uses(p, a)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

