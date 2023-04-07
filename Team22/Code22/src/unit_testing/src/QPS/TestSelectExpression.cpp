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

TEST_CASE("TestCase3_ParseSelectTupleSingleSynonym_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "stmt s; variable v;";
    string query = "Select <s> such that Uses(s, v)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase3_ParseSelectMultipleSynonyms_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "stmt s, s1; variable v;";
    string query = "Select <s, s1, v> such that Uses(s, v)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase3_ParseSelectTupleMultipleSynonymsWithAttrs_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "stmt s, s1; variable v;";
    string query = "Select <s.stmt#, s1, v, v.varName, s1.stmt#> such that Uses(s, v)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    ::printf("%s\n", actualResult->toString().c_str());

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase3_ParseSelectTupleMultipleSynonymsWithAttrsWhitespaces_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "stmt s, s1; variable v;";
    string query = "Select  <  s.stmt#  ,  s1  ,  v  ,  v.varName  ,  s1.stmt#  >   such that Uses(s, v)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = "Select <s.stmt#, s1, v, v.varName, s1.stmt#> such that Uses(s, v)";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase3_ParseSelectTupleMultipleSynonymsWithWhitespaces_SyntaxError") {
    QueryParser queryParser;
    string declaration = "stmt s, s1; variable v;";
    string query = "Select  <  s. stmt#  ,  s1  ,  v  ,  v.varName  ,  s1.stmt#  >   such that Uses(s, v)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }
    REQUIRE(throwsException);
}


TEST_CASE("TestCase3_ParseSelectTupleMultipleSynonymsWithInvalidAttrs_SemanticError") {
    QueryParser queryParser;
    string declaration = "stmt s, s1; variable v;";
    string query = "Select <s.stmt#, s1, v, v.stmt#, s1.varName> such that Uses(s, v)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase3_ParseSelectTupleNoSynonyms_SyntaxError") {
    QueryParser queryParser;
    string declaration = "stmt s, s1; variable v;";
    string query = "Select < > such that Uses(s, v)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase3_ParseSelectTupleNoSynonymsWithComma_SyntaxError") {
    QueryParser queryParser;
    string declaration = "stmt s, s1; variable v;";
    string query = "Select < , , > such that Uses(s, v)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase3_ParseSelectTupleInvalidSynonym_SyntaxError") {
    QueryParser queryParser;
    string declaration = "stmt s, s1; variable v;";
    string query = "Select < 1.varName > such that Uses(s, v)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase3_ParseSelectBOOLEANValid_Success") {
    QueryParser queryParser;
    string declaration = "stmt s, s1; variable v;";
    string query = "Select BOOLEAN such that Follows(1, 2)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = "Select BOOLEAN such that Follows(1, 2)";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase3_ParseSelectReturnBOOLEANInTuple_SemanticException") {
    QueryParser queryParser;
    string declaration = "stmt s, s1; variable v;";
    string query = "Select <s, BOOLEAN> such that Follows(s, 2)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase3_ParseSelectReturnBOOLEANWhitespaces_Success") {
    QueryParser queryParser;
    string declaration = "stmt s, s1; variable v;";
    string query = "Select    BOOLEAN   such that Follows(1, 2)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = "Select BOOLEAN such that Follows(1, 2)";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase3_ParseSelectReturnBOOLEANDeclaredAsStmt_Success") {
    QueryParser queryParser;
    string declaration = "stmt BOOLEAN; assign a1;";

    queryParser.parse(declaration);

    SECTION("inside tuple") {
        string query = "Select <BOOLEAN, a1> such that Follows(1, 2)";
        string expected = "Select <BOOLEAN, a1> such that Follows(1, 2)";
        SelectExpression *actualResult = queryParser.parse(query);
        REQUIRE(actualResult->toString() == expected);
    }

    SECTION("accessing stmt#") {
        string query = "Select BOOLEAN.stmt# such that Follows(1, 2)";
        string expected = "Select BOOLEAN.stmt# such that Follows(1, 2)";
        SelectExpression *actualResult = queryParser.parse(query);
        REQUIRE(actualResult->toString() == expected);
    }

}

TEST_CASE("TestCase3_ParseSelectReturnBOOLEANNotDeclaredAsStmt_SemanticError") {
    QueryParser queryParser;
    string declaration = "assign a1;";

    queryParser.parse(declaration);

    string query = "Select BOOLEAN.stmt# such that Follows(1, 2)";

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase3_ParseInvalidInteger") {
    QueryParser queryParser;
    string declaration = "stmt s; assign a;";

    queryParser.parse(declaration);

    SECTION ("InvalidIntInDesignEntity_SyntaxError") {
        string query = "Select s such that Follows(s, 06)";

        bool throwsException = false;

        try {
            Expression *exp1 = queryParser.parse(query);
        } catch (SyntacticException& e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }

    SECTION ("InvalidIntInAttrCond_SyntaxError") {
        string query = "Select s such that s.stmt# = 06";

        bool throwsException = false;

        try {
            Expression *exp1 = queryParser.parse(query);
        } catch (SyntacticException& e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }

    SECTION ("InvalidIntInIdent_Success") {
        string query = R"(Select s pattern a(_,_"x + 01"_))";
        string expected = R"(Select s such that pattern a(_, _+x01_))";

        SelectExpression *actualResult = queryParser.parse(query);
        REQUIRE(actualResult->toString() == expected);
    }

}

TEST_CASE("TestCase3_DuplicateClauseElimination") {
    QueryParser queryParser;
    string declaration = "stmt s; assign a;";

    queryParser.parse(declaration);

    SECTION ("RepeatedPatters_Success") {
        string query = R"(Select s pattern a(_,_"x + 01"_) pattern a(_,_"x + 01"_) pattern a(_,_"x + 01"_))";
        string expected = R"(Select s such that pattern a(_, _+x01_))";

        SelectExpression *actualResult = queryParser.parse(query);
        REQUIRE(actualResult->toString() == expected);
    }

}



