//
// Created by Tanishq Sharma on 4/4/23.
//

#include "QPS/Parser/Parser.h"
#include "catch.hpp"
#include "QPS/Exceptions/Exceptions.h"

using namespace std;

TEST_CASE("TestCase11_ParseSelectWithSuchThatNext_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a;";
    string query = "Select a such that Next(12, a)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase19_ParseSelectWithSuchThatNextWildCard_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a;";
    string query = "Select a such that Next(a, _)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase20_ParseSelectWithSuchThatNextSynonyms_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a; while w;";
    string query = "Select a such that Next(a, w)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase21_ParseSelectWithSuchThatNext*_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "while w;";
    string query = "Select w such that Next*(w, 12)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase22_ParseSelectWithSuchThatNext*WildCard_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a;";
    string query = "Select a such that Next*(_, a)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase23_ParseSelectWithSuchThatNext*Synonyms_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a; while w;";
    string query = "Select a such that Next*(w, a)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase23_ParseSelectWithSuchThatNext*SynonymsWhitespaces_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a; while w;";
    string query = "Select a such that   Next*  (  w  ,   a  )  ";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);
    string expected = "Select a such that Next*(w, a)";

    REQUIRE(actualResult->toString() == expected);
}

//undeclared synonyms
TEST_CASE("TestCase33_UndeclaredStmtEntityArg1NextExpression_SemanticError") {
    QueryParser queryParser;

    string declaration = "variable v;";
    string query = "Select v such that Next(w, v)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase34_UndeclaredStmtEntityArg2Next*Expression_SemanticError") {
    QueryParser queryParser;

    string declaration = "variable v;";
    string query = "Select v such that Next*(v, w)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}
