//
// Created by Tanishq Sharma on 5/4/23.
//

#include "QPS/Parser/Parser.h"
#include "catch.hpp"
#include "QPS/Exceptions/Exceptions.h"

using namespace std;

TEST_CASE("TestCase11_ParseSelectWithSuchThatAffects_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a;";
    string query = "Select a such that Affects(12, a)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase19_ParseSelectWithSuchThatAffectsWildCard_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a;";
    string query = "Select a such that Affects(a, _)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase20_ParseSelectWithSuchThatAffectsSynonyms_SemanticError") {
    QueryParser queryParser;
    string declaration = "assign a; while w;";
    string query = "Select a such that Affects(a, w)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase21_ParseSelectWithSuchThatAffects*_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a;";
    string query = "Select a such that Affects*(a, 12)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase22_ParseSelectWithSuchThatAffects*WildCard_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a;";
    string query = "Select a such that Affects*(_, a)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase23_ParseSelectWithSuchThatAffects*Arg2If_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a; if i;";
    string query = "Select a such that Affects*(w, i)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase23_ParseSelectWithSuchThatAffects*SynonymsWhitespaces_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a1, a2; while w;";
    string query = "Select <a1, a2> such that   Affects*  (  a1  ,   a2  )  ";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);
    string expected = "Select <a1, a2> such that Affects*(a1, a2)";

    REQUIRE(actualResult->toString() == expected);
}

//undeclared synonyms
TEST_CASE("TestCase33_UndeclaredStmtEntityArg1AffectsExpression_SemanticError") {
    QueryParser queryParser;

    string declaration = "variable v;";
    string query = "Select v such that Affects(w, v)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase34_UndeclaredStmtEntityArg2Affects*Expression_SemanticError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v such that Affects*(v, a)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}
