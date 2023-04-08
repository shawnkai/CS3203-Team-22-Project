//
// Created by Tanishq Sharma on 7/3/23.
//

#include "QPS/QueryParser/QueryParser.h"
#include "catch.hpp"
#include "QPS/Exceptions/Exceptions.h"

using namespace std;

TEST_CASE("TestCase13_ParseSelectWithSuchThatUses_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "variable v;";
    string query = "Select v such that Uses(1, v)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase14_ParseSelectWithSuchThatUsesWithIdent_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "variable v; procedure p;";
    string query = "Select p such that Uses(p, \"x\")";

    queryParser.parse(declaration);
    SelectExpression *actualResult = queryParser.parse(query);
    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase15_ParseSelectWithSuchThatUsesWithWildCard_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "variable v; procedure p;";
    string query = "Select p such that Uses(p, _)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase15_ParseSelectWithSuchThatUsesWithArg1Ident_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "variable v; procedure p;";
    string query = "Select p such that Uses(\"proc\", _)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase36_UndeclaredNamedEntityArg2UsesSExpression_SemanticError") {
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

TEST_CASE("TestCase37_UndeclaredNamedEntityArg2UsesPExpression_SemanticError") {
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

TEST_CASE("TestCase57_ModifiesExpressionFirstArgWildcard_SemanticError") {
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

TEST_CASE("TestCase58_UsesExpressionFirstArgWildcard_SemanticError") {
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

TEST_CASE("TestCase58_UsesExpressionFirstArgRead_SemanticError") {
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

TEST_CASE("TestCase58_UsesSExpressionSecondArgConstant_SemanticError") {
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

TEST_CASE("TestCase58_UsesPExpressionSecondArgAssign_SemanticError") {
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

