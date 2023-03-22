//
// Created by Tanishq Sharma on 13/3/23.
//

#include "QPS/Parser/Parser.h"
#include "catch.hpp"
#include "QPS/Exceptions/Exceptions.h"

using namespace std;

TEST_CASE("TestCase1_ParseSelectAtt_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a; variable v; procedure p;";
    string query = "Select v.varName such that Modifies(a, v)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);
    string expectedResult = query;

    REQUIRE(actualResult->toString() == expectedResult);
}

TEST_CASE("TestCase2_ParseSelectSelectAttValidWhitespaces_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "procedure p, q; variable v;";
    string query = R"(Select    p.procName   such that Modifies (q, v) with v.varName = "x" such that Modifies (p, "i"))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    ::printf("%s\n", actualResult->toString().c_str());

    string expected = R"(Select p.procName such that Modifies(q, v) Modifies(p, "i") with v.varName = "x")";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase3_ParseSelectSelectAtt_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "stmt s; call c; variable v;";
    string query = "Select s.stmt# such that Uses(s, v)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    ::printf("%s\n", actualResult->toString().c_str());

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase12_ParseSelectAttWrongAttrType_SemanticException") {
QueryParser queryParser;
string declaration = "variable v; assign a1;";
string query = "Select v.stmt# such that Uses(a1, v)";

queryParser.parse(declaration);

bool throwsException = false;

try {
Expression *exp1 = queryParser.parse(query);
} catch (SemanticException& e) {
throwsException = true;
}

REQUIRE(throwsException);
}

TEST_CASE("TestCase12_ParseSelectAttrInvaidAttr_SemanticException") {
    QueryParser queryParser;
    string declaration = "variable v; assign a1;";
    string query = "Select v.someAttr such that Uses(a1, v)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase14_ParseSelectAttrPeriodInAttr_SyntacticException") {
QueryParser queryParser;
string declaration = "variable v; assign a1;";
string query = "Select v.varName.varName such that Uses(a1, v)";

queryParser.parse(declaration);

bool throwsException = false;

try {
Expression *exp1 = queryParser.parse(query);
} catch (SyntacticException& e) {
throwsException = true;
}

REQUIRE(throwsException);
}