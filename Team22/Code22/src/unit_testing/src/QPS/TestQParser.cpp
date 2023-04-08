//
// Created by Atin Sakkeer Hussain on 04/02/2023.
//

#include "QPS/QueryParser/QueryParser.h"
#include "catch.hpp"
#include "QPS/Exceptions/Exceptions.h"

using namespace std;

TEST_CASE("TestCase1_ParsingDeclarationStatement_ShouldCreateDesignEntityForEach") {
    QueryParser queryParser;

    string declaration = "assign a, a1; stmt s, s1; while w; if ifs; variable v, v1; procedure p, q; constant c; read re; print pn; call cl;";

    queryParser.parse(declaration);

    SynonymTable actualTable = queryParser.getSynonymTable();

    unordered_map<string, string> expectedTable = {{"s", "STATEMENT"}, {"s1", "STATEMENT"}, {"a", "ASSIGNMENT"}, {"a1", "ASSIGNMENT"},
                                         {"w", "WHILE"}, {"ifs", "IF"}, {"v", "VARIABLE"}, {"v1", "VARIABLE"},
                                         {"p", "PROCEDURE"}, {"q", "PROCEDURE"}, {"c", "CONSTANT"}, {"re", "READ"},
                                         {"pn", "PRINT"}, {"cl", "CALL"}};

    REQUIRE(actualTable.isEquivalentTo(expectedTable));
}


TEST_CASE("TestCase2_ParsingDeclarationStatementSwitchedOrder_Success") {
    QueryParser queryParser;

    string declaration = "stmt s, s1; assign a, a1; while w; if ifs; variable v, v1; procedure p, q; constant c; read re; print pn; call cl;";

    queryParser.parse(declaration);

    SynonymTable actualTable = queryParser.getSynonymTable();

    unordered_map<string, string> expectedTable = {{"s", "STATEMENT"}, {"s1", "STATEMENT"}, {"a", "ASSIGNMENT"}, {"a1", "ASSIGNMENT"},
                                         {"w", "WHILE"}, {"ifs", "IF"}, {"v", "VARIABLE"}, {"v1", "VARIABLE"},
                                         {"p", "PROCEDURE"}, {"q", "PROCEDURE"}, {"c", "CONSTANT"}, {"re", "READ"},
                                         {"pn", "PRINT"}, {"cl", "CALL"}};

    REQUIRE(actualTable.isEquivalentTo(expectedTable));
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

TEST_CASE("TestCase6_ParsingDeclarationSynonymEndingWithUnderscore_Success") {
    QueryParser queryParser;

    string declaration = "stmt s; assign a_;";

    queryParser.parse(declaration);

    SynonymTable resultTable = queryParser.getSynonymTable();

    unordered_map<string, string> expectedTable = {{"s", "STATEMENT"}, {"a_", "ASSIGNMENT"}};

    REQUIRE(resultTable.isEquivalentTo(expectedTable));
}

TEST_CASE("TestCase6_ParsingDeclarationSynonymWith*InMiddle_SyntaxError") {
    QueryParser queryParser;

    string declaration = "stmt s; assign a*b;";

    REQUIRE(!queryParser.isDeclaration(declaration));

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

    SynonymTable resultTable = queryParser.getSynonymTable();

    unordered_map<string, string> expectedTable = {{"stmt", "STATEMENT"}, {"s1", "STATEMENT"}, {"assign", "ASSIGNMENT"}, {"a1", "ASSIGNMENT"},
                                         {"while", "WHILE"}, {"if", "IF"}, {"variable", "VARIABLE"}, {"v1", "VARIABLE"},
                                         {"procedure", "PROCEDURE"}, {"q", "PROCEDURE"}, {"constant", "CONSTANT"}, {"read", "READ"},
                                         {"print", "PRINT"}, {"call", "CALL"}};

    REQUIRE(resultTable.isEquivalentTo(expectedTable));
}

TEST_CASE("TestCase8_ParsingDeclarationStatementSameTypeSeperatelyDeclared_Success") {
    QueryParser queryParser;

    string declaration = "assign a; assign a1; stmt s1; while w; if ifs; variable v, v1; stmt s; procedure p, q; constant c; read re; print pn; call cl;";

    queryParser.parse(declaration);

    SynonymTable resultTable = queryParser.getSynonymTable();

    unordered_map<string, string> expectedTable = {{"s", "STATEMENT"}, {"s1", "STATEMENT"}, {"a", "ASSIGNMENT"}, {"a1", "ASSIGNMENT"},
                                         {"w", "WHILE"}, {"ifs", "IF"}, {"v", "VARIABLE"}, {"v1", "VARIABLE"},
                                         {"p", "PROCEDURE"}, {"q", "PROCEDURE"}, {"c", "CONSTANT"}, {"re", "READ"},
                                         {"pn", "PRINT"}, {"cl", "CALL"}};

    REQUIRE(resultTable.isEquivalentTo(expectedTable));

}

TEST_CASE("TestCase9_ParseSelectStatement_ShouldSuccess") {
    QueryParser queryParser;
    string declaration = "variable v;";
    string query = "Select v";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    REQUIRE(actualResult->toString() == query);
}

//TEST_CASE("TestCase11_ParseSelectWithSuchThatModifiesWithIdent_ShouldSuccess") {
//    QueryParser queryParser;
//    string declaration = "variable v; procedure p;";
//    string query = "Select p such that Modifies(p, \"x\")";
//
//    queryParser.parse(declaration);
//
//    bool throwsException = false;
//
//    try {
//        Expression *exp1 = queryParser.parse(query);
//    } catch (SyntacticException& e) {
//        throwsException = true;
//    }
//
//    REQUIRE(throwsException);
//
//}

TEST_CASE("TestCase10_InvalidSelectKeyword_SyntaxError") {
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

TEST_CASE("TestCase11_MultipleSelectOccurrence_SyntaxError") {
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


TEST_CASE("TestCase12_OneInvalidDesignAbstraction_SyntaxError") {
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

//undeclared synonyms

TEST_CASE("TestCase13_ParsingDeclarationStatementMoreWhitespacesInserted_Success") {
    QueryParser queryParser;

    string declaration = "assign a;   assign  a1; stmt   s1;  while w; if ifs;variable v, v1;stmt s;procedure p, q; constant c; read re; print pn; call cl;";
    queryParser.parse(declaration);

    SynonymTable resultTable = queryParser.getSynonymTable();

    unordered_map<string, string> expectedTable = {{"s", "STATEMENT"}, {"s1", "STATEMENT"}, {"a", "ASSIGNMENT"}, {"a1", "ASSIGNMENT"},
                                         {"w", "WHILE"}, {"ifs", "IF"}, {"v", "VARIABLE"}, {"v1", "VARIABLE"},
                                         {"p", "PROCEDURE"}, {"q", "PROCEDURE"}, {"c", "CONSTANT"}, {"re", "READ"},
                                         {"pn", "PRINT"}, {"cl", "CALL"}};

    REQUIRE(resultTable.isEquivalentTo(expectedTable));

}

TEST_CASE("TestCase14_ParsingDeclarationStatementMoreWhitespacesInserted_Success") {
    QueryParser queryParser;

    string declaration = "assign a;   assign  a1; stmt   s1;  while w; if ifs;variable v, v1;stmt s;procedure p, q; constant c; read re; print pn; call cl;";

    queryParser.parse(declaration);

    SynonymTable resultTable = queryParser.getSynonymTable();

    unordered_map<string, string> expectedTable = {{"s", "STATEMENT"}, {"s1", "STATEMENT"}, {"a", "ASSIGNMENT"}, {"a1", "ASSIGNMENT"},
                                         {"w", "WHILE"}, {"ifs", "IF"}, {"v", "VARIABLE"}, {"v1", "VARIABLE"},
                                         {"p", "PROCEDURE"}, {"q", "PROCEDURE"}, {"c", "CONSTANT"}, {"re", "READ"},
                                         {"pn", "PRINT"}, {"cl", "CALL"}};

    REQUIRE(resultTable.isEquivalentTo(expectedTable));

}


TEST_CASE("TestCase15_andClauseAfterSuchThat_Success") {
    string query = "Select v such that Uses(3, v) and Uses(4, v)";

    string actualResult = QueryParser::replaceAnd(query);

    string expected = "Select v such that Uses(3, v) such that Uses(4, v)";
    REQUIRE(actualResult == expected);
}

TEST_CASE("TestCase16_andClauseRightAfterSuchThat_FailsValidation") {
    QueryParser queryParser;
    string query = "Select v such that and Uses(3, v)";

    string actualResult = QueryParser::replaceAnd(query);

    string expected = "Select v such that such that Uses(3, v)";

    REQUIRE(actualResult == expected);

    REQUIRE(!queryParser.isValidQuery(actualResult));
}


TEST_CASE("TestCase17_andAsFirstConnective_SyntaxError") {
    QueryParser queryParser;
    string query = "Select v and Uses(3, v) such that Uses(4, v)";
    bool throwsException = false;

    try {
        string actualResult = QueryParser::replaceAnd(query);
    }
    catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase18_andClauseAfterWith_Success") {

    string query = "Select <s1, s2> with s1.stmt# = 3 and s2.stmt# = 4";

    string actualResult = QueryParser::replaceAnd(query);

    string expected = "Select <s1, s2> with s1.stmt# = 3 with s2.stmt# = 4";
    REQUIRE(actualResult == expected);
}

TEST_CASE("TestCase19_andClauseAfterPattern_Success") {
    string query = "Select a pattern a(x, _) and a(x, _\"x\"_) ";

    string actualResult = QueryParser::replaceAnd(query);

    string expected = "Select a pattern a(x, _) pattern a(x, _\"x\"_)";
    REQUIRE(actualResult == expected);
}

TEST_CASE("TestCase62_ParseDeclarationOfMultipleSynsOfSameTypeWithoutSpace_Success") {
    QueryParser queryParser;

    string declaration = "assign a; variable v,v1;";

    queryParser.parse(declaration);

    SynonymTable resultTable = queryParser.getSynonymTable();

    unordered_map<string, string> expectedTable = {{"a", "ASSIGNMENT"}, {"v", "VARIABLE"}, {"v1", "VARIABLE"}};

    REQUIRE(resultTable.isEquivalentTo(expectedTable));
}

TEST_CASE("TestCase62_ParseDeclarationOfMultipleSynsOfSameTypeWithoutSpace2_Success") {
    QueryParser queryParser;

    string declaration = "assign a,a1; variable v;";

    queryParser.parse(declaration);

    SynonymTable resultTable = queryParser.getSynonymTable();

    unordered_map<string, string> expectedTable = {{"a", "ASSIGNMENT"}, {"a1", "ASSIGNMENT"}, {"v", "VARIABLE"}};

    REQUIRE(resultTable.isEquivalentTo(expectedTable));
}
