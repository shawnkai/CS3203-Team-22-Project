//
// Created by Atin Sakkeer Hussain on 04/02/2023.
//


#include "QPS/Parser.h"
#include "catch.hpp"
#include "QPS/Exceptions.h"

using namespace std;

TEST_CASE("TestCase1_ParsingDeclarationStatement_ShouldCreateDesignEntityForEach") {
    QueryParser queryParser;

    string declaration = "assign a, a1; stmt s, s1; while w; if ifs; variable v, v1; procedure p, q; constant c; read re; print pn; call cl;";

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


TEST_CASE("TestCase2_ParsingDeclarationStatementSwitchedOrder_Success") {
    QueryParser queryParser;

    string declaration = "stmt s, s1; assign a, a1; while w; if ifs; variable v, v1; procedure p, q; constant c; read re; print pn; call cl;";

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

TEST_CASE("TestCase3_ParsingDeclarationStatementInvalidType_SyntaxError") {
    QueryParser queryParser;

    string declaration = "statement s, s1; assign a, a1;";

    REQUIRE(!queryParser.isDeclaration(declaration));

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(declaration);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase4_ParsingDeclarationNoSemicolon_SyntaxError") {
    QueryParser queryParser;

    string declaration = "statement s, s1; assign a, a1";

    REQUIRE(!queryParser.isDeclaration(declaration));

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(declaration);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase5_ParsingDeclarationRedeclaredSynonyms_SyntaxError") {
    QueryParser queryParser;

    string declaration = "stmt s; assign s;";

    REQUIRE(queryParser.isDeclaration(declaration));

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(declaration);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase6_ParsingDeclarationNonAlphanumericSynonym_SyntaxError") {
    QueryParser queryParser;

    string declaration = "stmt s; assign a_;";

    REQUIRE(queryParser.isDeclaration(declaration));

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(declaration);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase7_ParsingDeclarationStatementSynonymNameSameAsType_Success") {
    QueryParser queryParser;

    string declaration = "stmt stmt, s1; assign assign, a1; while while; if if; variable variable, v1; procedure procedure, q; constant constant; read read; print print; call call;";

    queryParser.parse(declaration);

    vector<tuple<string, string>> result = queryParser.getSynonymTable();

    map<string, string> expectedTable = {{"stmt", "STATEMENT"}, {"s1", "STATEMENT"}, {"assign", "ASSIGNMENT"}, {"a1", "ASSIGNMENT"},
                                         {"while", "WHILE"}, {"if", "IF"}, {"variable", "VARIABLE"}, {"v1", "VARIABLE"},
                                         {"procedure", "PROCEDURE"}, {"q", "PROCEDURE"}, {"constant", "CONSTANT"}, {"read", "READ"},
                                         {"print", "PRINT"}, {"call", "CALL"}};

    map<string, string> actualTable;
    for (auto & i : result) {
        actualTable[get<0>(i)] = get<1>(i);
    }

    REQUIRE(actualTable == expectedTable);
}

TEST_CASE("TestCase8_ParsingDeclarationStatementSameTypeSeperatelyDeclared_Success") {
    QueryParser queryParser;

    string declaration = "assign a; assign a1; stmt s1; while w; if ifs; variable v, v1; stmt s; procedure p, q; constant c; read re; print pn; call cl;";

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


TEST_CASE("TestCase9_ParseSelectStatement_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "variable v;";
    string query = "Select v";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase10_ParseSelectWithSuchThatModifies_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "variable v;";
    string query = "Select v such that Modifies(1, v)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase11_ParseSelectWithSuchThatModifiesWithIdent_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "variable v; procedure p;";
    string query = "Select p such that Modifies(p, \"x\")";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase12_ParseSelectWithSuchThatModifiesWithWildCard_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "procedure p;";
    string query = "Select p such that Modifies(p, _)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

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

TEST_CASE("TestCase16_ParseSelectWithExactMatchingPattern_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a;";
    string query = R"(Select a pattern a(_, "x+y"))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(_, +xy))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase17_ParseSelectWithWildCardPattern_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a;";
    string query = R"(Select a pattern a(_, _"x+y"_))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(_, _+xy_))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase18_ParseSelectWithSuchThatFollows_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a;";
    string query = "Select a such that Follows(12, a)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase19_ParseSelectWithSuchThatFollowsWildCard_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a;";
    string query = "Select a such that Follows(a, _)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase20_ParseSelectWithSuchThatFollowsSynonyms_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a; while w;";
    string query = "Select a such that Follows(a, w)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase21_ParseSelectWithSuchThatParent_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "while w;";
    string query = "Select w such that Parent(w, 12)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase22_ParseSelectWithSuchThatParentWildCard_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a;";
    string query = "Select a such that Parent(_, a)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase23_ParseSelectWithSuchThatParentSynonyms_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "assign a; while w;";
    string query = "Select a such that Parent(w, a)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

TEST_CASE("TestCase24_InvalidSelectKeyword_SyntaxError") {
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

TEST_CASE("TestCase25_MultipleSelectOccurrence_SyntaxError") {
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


TEST_CASE("TestCase26_OneInvalidDesignAbstraction_SyntaxError") {
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
TEST_CASE("TestCase27_MissingOpeningQuoteWithoutWildcardsPatternExpression_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v pattern a(v, x+y\")";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase28_MissingClosingQuotePatternWithoutWildcardsExpression_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v pattern a(v, \"x+y)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase29_MissingClosingWildcardWithValidQuotesPatternExpression_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v pattern a(v, _\"x+y\")";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase30_MissingOpeningQuoteWithValidWildcardsPatternExpression_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v pattern a(v, \"x+y\"_)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase31_MissingAllQuotesWithNoWildcardPatternExpression_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v pattern a(v, x+y)";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase32_MissingAllQuotesWithValidWildcardPatternExpression_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v pattern a(v, _x+y_)";

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
TEST_CASE("TestCase33_UndeclaredStmtEntityArg1FollowsExpression_SemanticError") {
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


TEST_CASE("TestCase34_UndeclaredStmtEntityArg2FollowsExpression_SemanticError") {
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

TEST_CASE("TestCase35_UndeclaredVariableArg1ModifiesPExpression_SemanticError") {
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

TEST_CASE("TestCase36_UndeclaredNamedEntityArg2UsesSExpression_SemanticError") {
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

TEST_CASE("TestCase38_UndeclaredNamedEntityArg2ModifiesSExpression_SemanticError") {
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

TEST_CASE("TestCase39_UndeclaredNamedEntityArg2ModifiesPExpression_SemanticError") {
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

TEST_CASE("TestCase39_UndeclaredNamedEntitySelectExpression_SemanticError") {
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

TEST_CASE("TestCase40_InvalidSymbolsExpressionSpecPatternExpression_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v pattern a(v, \"__\")";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase41_SuchThatPatternExpression_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = R"(Select a such that pattern a(_, "x+y"))";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}


//whitespace tests
TEST_CASE("TestCase42_WhitespaceOnLeftSideArg1PatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = R"(Select a pattern a( _, "x+y"))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(_, +xy))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase43_WhitespaceOnRightSideArg1PatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = R"(Select a pattern a(v  , "x+y"))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(v, +xy))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase44_MultipleWhitespaceOnBothSidesBothArgsPatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v pattern a(    v  ,   \"x+y\"  )";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select v such that pattern a(v, +xy))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase45_NoWhitespaceBothArgsPatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = R"(Select a pattern a(_,"x+y"))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(_, +xy))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase46_OneWhitespacesAfterSynAssignPatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = R"(Select a pattern a ( _ , "x+y"))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(_, +xy))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase47_MultipleWhitespacesAfterSynAssignPatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = R"(Select a pattern a  ( _ ,  "x+y"  ))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(_, +xy))";

    REQUIRE(actualResult->toString() == expected);
}


TEST_CASE("TestCase48_ParsingDeclarationStatementMoreWhitespacesInserted_Success") {
    QueryParser queryParser;

    string declaration = "assign a;   assign  a1; stmt   s1;  while w; if ifs;variable v, v1;stmt s;procedure p, q; constant c; read re; print pn; call cl;";
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

TEST_CASE("TestCase49_SuchThatPatternExpression_SyntaxError") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = R"(Select a such that pattern a(_, "x+y"))";

    queryParser.parse(declaration);

    bool throwsException = false;

    try {
        Expression *exp1 = queryParser.parse(query);
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}


//whitespace tests
TEST_CASE("TestCase50_WhitespaceOnLeftSideArg1PatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = R"(Select a pattern a( _, "x+y"))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(_, +xy))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase51_WhitespaceOnRightSideArg1PatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = R"(Select a pattern a(v  , "x+y"))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(v, +xy))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase52_MultipleWhitespaceOnBothSidesBothArgsPatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select v pattern a(    v  ,   \"x+y\"  )";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select v such that pattern a(v, +xy))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase53_NoWhitespaceBothArgsPatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = R"(Select a pattern a(_,"x+y"))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(_, +xy))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase54_OneWhitespacesAfterSynAssignPatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = R"(Select a pattern a ( _ , "x+y"))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(_, +xy))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase55_MultipleWhitespacesAfterSynAssignPatternExpression_Success") {
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = R"(Select a pattern a  ( _ ,  "x+y"  ))";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    string expected = R"(Select a such that pattern a(_, +xy))";

    REQUIRE(actualResult->toString() == expected);
}

TEST_CASE("TestCase56_ParsingDeclarationStatementMoreWhitespacesInserted_Success") {
    QueryParser queryParser;

    string declaration = "assign a;   assign  a1; stmt   s1;  while w; if ifs;variable v, v1;stmt s;procedure p, q; constant c; read re; print pn; call cl;";

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



