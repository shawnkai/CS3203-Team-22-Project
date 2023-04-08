//
// Created by Tanishq Sharma on 11/3/23.
//

#include "QPS/QueryParser/QueryParser.h"
#include "catch.hpp"
#include "QPS/Exceptions/Exceptions.h"

using namespace std;

TEST_CASE("TestCase1_ParseSelectWithWithWithSynonyms_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a; variable v; procedure p;";
    string query = "Select a such that Modifies(a, v) with v.varName = p.procName";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);
    string expectedResult = query;

    REQUIRE(actualResult->toString() == expectedResult);
}

TEST_CASE("TestCase2_ParseSelectWithWithValidWhitespaces_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "procedure p, q; variable v;";
    string query = R"(Select p such that Modifies (q, v)   with     v.varName  =   "  x  "  such that Modifies (p, "i"))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    ::printf("%s\n", actualResult->toString().c_str());

    string expected = R"(Select p such that Modifies(q, v) Modifies(p, "i") with v.varName = "x")";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase3_ParseSelectWithWithWithSynonyms_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "procedure p; call c; while w;";
    string query = "Select p such that Parent(w, c) with c.procName = p.procName";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    ::printf("%s\n", actualResult->toString().c_str());

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase4_ParseSelectWithWithWithSynonyms_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "stmt s; constant c;";
    string query = "Select s with s.stmt# = c.value";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    ::printf("%s\n", actualResult->toString().c_str());

    REQUIRE(actualResult->toString() == "Select s such that with s.stmt# = c.value");
}

TEST_CASE("TestCase5_ParseSelectWithWithWithSynonyms_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "procedure p; variable v;";
    string query = "Select p with p.procName = v.varName";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    ::printf("%s\n", actualResult->toString().c_str());

    REQUIRE(actualResult->toString() == "Select p such that with p.procName = v.varName");
}

TEST_CASE("TestCase6_ParseSelectWithWithWithSynonyms_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a; while w; stmt s;";
    string query = "Select a such that Parent* (w, a) and Follows* (60, s) pattern a(\"x\", _) with a.stmt# = s.stmt#";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    ::printf("%s\n", actualResult->toString().c_str());

    REQUIRE(actualResult->toString() == "Select a such that pattern a(x, _) Follows*(60, s) Parent*(w, a) with a.stmt# = s.stmt#");
}

TEST_CASE("TestCase7_ParseSelectWithWithWithSynonyms_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a, a1;";
    string query = "Select a1 with a.stmt# = 12";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    ::printf("%s\n", actualResult->toString().c_str());

    REQUIRE(actualResult->toString() == "Select a1 such that with a.stmt# = 12");
}

TEST_CASE("TestCase8_ParseSelectWithWithWithSynonyms_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a, a1;";
    string query = "Select a1 with 12 = a.stmt#";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    ::printf("%s\n", actualResult->toString().c_str());

    REQUIRE(actualResult->toString() == "Select a1 such that with 12 = a.stmt#");
}

TEST_CASE("TestCase9_ParseSelectWithWithMismatchingStringInt_SemanticError") {
    QueryParser queryParser;
    string declaration = "assign a, a1; call c;";
    string query = "Select a1 with \"Hello\" = a.stmt#";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase10_ParseSelectWithWithMismatchingIntString_SemanticError") {
    QueryParser queryParser;
    string declaration = "assign a, a1; read r;";
    string query = "Select a1 with 1 = \"Somestr\"";

    queryParser.parse(declaration);


    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase11_ParseSelectWithWithMismatchingIntString_SemanticError") {
    QueryParser queryParser;
    string declaration = "assign a, a1; read r;";
    string query = "Select a1 with a.stmt# = r.varName";

    queryParser.parse(declaration);


    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase12_ParseSelectWithWithWrongAttrType_SemanticException") {
    QueryParser queryParser;
    string declaration = "variable v; assign a1;";
    string query = "Select a1 with v.stmt# = 12";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase13_ParseSelectWithWithInvalidAttr_SemanticException") {
    QueryParser queryParser;
    string declaration = "variable v;";
    string query = "Select a1 with v.someAttr = 12";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase14_ParseSelectWithWithPeriodInAttr_SyntacticException") {
    QueryParser queryParser;
    string declaration = "variable v;";
    string query = "Select a1 with v.varName.varName = 12";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase15_ParseSelectWithWithInvalidLiteral_SyntacticException") {
    QueryParser queryParser;
    string declaration = "variable v; assign a1;";
    string query = "Select a1 with someVar = 1";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}


TEST_CASE("TestCase16_ParseSelectWithWithClauseWithThreeEquals_SyntacticException") {
    QueryParser queryParser;
    string declaration = "variable v; call c; read r;";
    string query = "Select a1 with v.varName = c.procName = r.varName";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}
