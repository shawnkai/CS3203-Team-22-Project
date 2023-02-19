//
// Created by Atin Sakkeer Hussain on 04/02/2023.
//


#include "QPS/Parser.h"
#include "catch.hpp"
#include "QPS/Exceptions.h"

using namespace std;

TEST_CASE("TestCase1_ParsingDeclarationStatement_ShouldCreateDesignEntityForEach") {
    QueryParser queryParser;

    string declaration = "stmt s, s1; assign a, a1; while w; if ifs; variable v, v1; procedure p, q; constant c; read re; print pn; call cl;";

    REQUIRE(queryParser.isDeclaration(declaration));

    queryParser.parse(declaration);

    vector<tuple<string, string>> result = queryParser.getSynonymTable();

    map<string, string> expectedTable = {{"s", "STATEMENT"}, {"s1", "STATEMENT"}, {"a", "ASSIGNMENT"}, {"a1", "ASSIGNMENT"},
                                         {"w", "WHILE"}, {"ifs", "IF"}, {"v", "VARIABLE"}, {"v1", "VARIABLE"},
                                         {"p", "PROCEDURE"}, {"q", "PROCEDURE"}, {"c", "CONSTANT"}, {"re", "READ"},
                                         {"pn", "PRINT"}, {"cl", "CALL"}};

    map<string, string> actualTable;
    for (auto & i : result) {
        actualTable[get<0>(i)] = get<1>(i);
    }

    REQUIRE(actualTable == expectedTable);
}

TEST_CASE("TestCase2_ParseSelectStatement_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "variable v;";
    string query = "Select v";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase3_ParseSelectWithSuchThatModifies_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "variable v;";
    string query = "Select v such that Modifies(1, v)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase4_ParseSelectWithSuchThatModifiesWithIdent_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "variable v; procedure p;";
    string query = "Select p such that Modifies(p, \"x\")";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase5_ParseSelectWithSuchThatModifiesWithWildCard_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "procedure p;";
    string query = "Select p such that Modifies(p, _)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase6_ParseSelectWithSuchThatUses_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "variable v;";
    string query = "Select v such that Uses(1, v)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase7_ParseSelectWithSuchThatUsesWithIdent_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "variable v; procedure p;";
    string query = "Select p such that Uses(p, \"x\")";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase8_ParseSelectWithSuchThatUsesWithWildCard_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "variable v; procedure p;";
    string query = "Select p such that Uses(p, _)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase9_ParseSelectWithExactMatchingPattern_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a;";
    string query = R"(Select a such that pattern a(_, "x+y"))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(_, +xy))";
    
    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase10_ParseSelectWithWildCardPattern_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a;";
    string query = R"(Select a such that pattern a(_, _"x+y"_))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(_, _+xy_))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase11_ParseSelectWithSuchThatFollows_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a;";
    string query = "Select a such that Follows(12, a)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase12_ParseSelectWithSuchThatFollowsWildCard_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a;";
    string query = "Select a such that Follows(a, _)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase12_ParseSelectWithSuchThatFollowsSynonyms_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a; while w;";
    string query = "Select a such that Follows(a, w)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase13_ParseSelectWithSuchThatParent_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "while w;";
    string query = "Select w such that Parent(w, 12)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase14_ParseSelectWithSuchThatParentWildCard_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a;";
    string query = "Select a such that Parent(_, a)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase15_ParseSelectWithSuchThatParentSynonyms_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a; while w;";
    string query = "Select a such that Parent(w, a)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase16_InvalidSelectKeyword_SyntaxError") {
    QueryParser queryParser;

    string query1 = "Sel v";

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query1);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);

}

TEST_CASE("TestCase17_MultipleSelectOccurrence_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; read r;";
    string query = "Select v such that Uses(1, v) Select v such that Uses(1, v)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);

}


TEST_CASE("TestCase18_OneInvalidDesignAbstraction_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; read r;";
    string query = "Select v such that InvalidEntity(1, h)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);

}

//Missing quotation marks, wildcard combinations
TEST_CASE("TestCase19_MissingOpeningQuoteWithoutWildcardsPatternExpression_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v such that pattern a(v, x+y\")";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase20_MissingClosingQuotePatternWithoutWildcardsExpression_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v such that pattern a(v, \"x+y)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase21_MissingClosingWildcardWithValidQuotesPatternExpression_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v such that pattern a(v, _\"x+y\")";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase22_MissingOpeningQuoteWithValidWildcardsPatternExpression_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v such that pattern a(v, \"x+y\"_)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase23_MissingAllQuotesWithNoWildcardPatternExpression_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v such that pattern a(v, x+y)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase24_MissingAllQuotesWithValidWildcardPatternExpression_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v such that pattern a(v, _x+y_)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}


//undeclared synonyms
TEST_CASE("TestCase25_UndeclaredStmtEntityArg1FollowsExpression_SemanticError") {
    QueryParser queryParser;

    string declaration = "variable v;";
    string query = "Select v such that Follows(w, v)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}


TEST_CASE("TestCase26_UndeclaredStmtEntityArg2FollowsExpression_SemanticError") {
    QueryParser queryParser;

    string declaration = "variable v;";
    string query = "Select v such that Follows(v, w)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase27_UndeclaredVariableArg1ModifiesPExpression_SemanticError") {
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

TEST_CASE("TestCase28_UndeclaredNamedEntityArg2UsesSExpression_SemanticError") {
    QueryParser queryParser;

    string declaration = "variable v; read r;";
    string query = "Select v such that Uses(r, a)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase29_UndeclaredNamedEntityArg2UsesPExpression_SemanticError") {
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

TEST_CASE("TestCase30_UndeclaredNamedEntityArg2ModifiesSExpression_SemanticError") {
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

TEST_CASE("TestCase31_UndeclaredNamedEntityArg2ModifiesPExpression_SemanticError") {
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

TEST_CASE("TestCase32_InvalidSymbolsExpressionSpecPatternExpression_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v such that pattern a(v, \"__\")";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}






