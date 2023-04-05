#include "SP/DesignExtractor/DesignExtractor.h"
#include "catch.hpp"
using namespace std;
TEST_CASE("Testcase1_ExtractSimpleStatement_ShouldSuccess") {
    TNode variable1 = TNode(TokenType::NAME_IDENTIFIER, "y", 1, std::vector<TNode>(0));
    TNode print1 = TNode(TokenType::PRINT, "print", 1, std::vector<TNode>(0));
    std::vector<TNode> child2;
    child2.push_back(variable1);
    print1.children = child2;

    TNode stmtlist1 = TNode(TokenType::STATEMENT_LIST, "stmtList", 1, std::vector<TNode>(0));
    std::vector<TNode> child1;
    child1.push_back(print1);
    stmtlist1.children = child1;

    TNode procedure1 = TNode(TokenType::PROCEDURE, "main", 0, std::vector<TNode>(0));
    std::vector<TNode> child;
    child.push_back(stmtlist1);
    procedure1.children = child;

    TNode root = TNode(TokenType::PROGRAM, "program", 0, std::vector<TNode>(0));
    std::vector<TNode> child3;
    child3.push_back(procedure1);
    root.children = child3;

    /*PKB pkbinstance = PKB();
    pkbinstance.clearAllDatabases();
    DesignExtractor designExtractor;

    designExtractor.extractAbstraction(root, pkbinstance);

    std::string result1 = pkbinstance.getDesignEntity("VARIABLE", "y").toString();
    std::string result2 = pkbinstance.getDesignAbstraction("USES", make_tuple("STATEMENT", "y")).toString();
    REQUIRE(result1 == "VARIABLE: y: 1, ");
    REQUIRE(result2 == "USES:STATEMENT: y: 1, ");*/
}

TEST_CASE("Testcase2_ExtractComplexStatement_ShouldSuccess") {

    TNode variable7 = TNode(TokenType::NAME_IDENTIFIER, "x", 5, std::vector<TNode>(0));
    TNode read2 = TNode(TokenType::READ, "read", 4, std::vector<TNode>(0));
    std::vector<TNode> child11;
    child11.push_back(variable7);
    read2.children = child11;

    TNode stmtlist4 = TNode(TokenType::STATEMENT_LIST, "stmtList", 3, std::vector<TNode>(0));
    std::vector<TNode> child10;
    child10.push_back(read2);
    stmtlist4.children = child10;

    TNode variable6 = TNode(TokenType::NAME_IDENTIFIER, "k", 4, std::vector<TNode>(0));
    TNode print1 = TNode(TokenType::PRINT, "print", 4, std::vector<TNode>(0));
    std::vector<TNode> child9;
    child9.push_back(variable6);
    print1.children = child9;

    TNode stmtlist3 = TNode(TokenType::STATEMENT_LIST, "stmtList", 3, std::vector<TNode>(0));
    std::vector<TNode> child8;
    child8.push_back(print1);
    stmtlist3.children = child8;

    TNode condition2 = TNode(TokenType::OPERATOR, ">", 3, std::vector<TNode>(0));
    TNode variable4 = TNode(TokenType::NAME_IDENTIFIER, "x", 3, std::vector<TNode>(0));
    TNode variable5 = TNode(TokenType::NAME_IDENTIFIER, "a", 3, std::vector<TNode>(0));
    std::vector<TNode> child7;
    child7.push_back(variable4);
    child7.push_back(variable5);
    condition2.children = child7;
    TNode if1 = TNode(TokenType::IF, "if", 3, std::vector<TNode>(0));
    std::vector<TNode> child6;
    child6.push_back(condition2);
    child6.push_back(stmtlist3);
    child6.push_back(stmtlist4);
    if1.children = child6;

    TNode stmtlist2 = TNode(TokenType::STATEMENT_LIST, "stmtList", 2, std::vector<TNode>(0));
    std::vector<TNode> child5;
    child5.push_back(if1);
    stmtlist2.children = child5;

    TNode condition1 = TNode(TokenType::OPERATOR, "<", 2, std::vector<TNode>(0));
    TNode variable2 = TNode(TokenType::NAME_IDENTIFIER, "x", 2, std::vector<TNode>(0));
    TNode variable3 = TNode(TokenType::NAME_IDENTIFIER, "z", 2, std::vector<TNode>(0));
    std::vector<TNode> child4;
    child4.push_back(variable2);
    child4.push_back(variable3);
    condition1.children = child4;
    TNode while1 = TNode(TokenType::WHILE, "while", 2, std::vector<TNode>(0));
    std::vector<TNode> child3;
    child3.push_back(condition1);
    child3.push_back(stmtlist2);
    while1.children = child3;

    TNode variable1 = TNode(TokenType::NAME_IDENTIFIER, "y", 1, std::vector<TNode>(0));
    TNode read1 = TNode(TokenType::READ, "read", 1, std::vector<TNode>(0));
    std::vector<TNode> child2;
    child2.push_back(variable1);
    read1.children = child2;

    TNode stmtlist1 = TNode(TokenType::STATEMENT_LIST, "stmtList", 1, std::vector<TNode>(0));
    std::vector<TNode> child1;
    child1.push_back(read1);
    child1.push_back(while1);
    stmtlist1.children = child1;

    TNode procedure1 = TNode(TokenType::PROCEDURE, "main", 0, std::vector<TNode>(0));
    std::vector<TNode> child;
    child.push_back(stmtlist1);
    procedure1.children = child;

    TNode root = TNode(TokenType::PROGRAM, "program", 0, std::vector<TNode>(0));
    std::vector<TNode> child12;
    child12.push_back(procedure1);
    root.children = child12;

    /*PKB pkbinstance = PKB();
    pkbinstance.clearAllDatabases();
    DesignExtractor designExtractor;

    designExtractor.extractAbstraction(root, pkbinstance);

    std::string result1 = pkbinstance.getDesignEntity("VARIABLE", "x").toString();
    std::string result2 = pkbinstance.getDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "x")).toString();
    std::string result3 = pkbinstance.getDesignAbstraction("USES", make_tuple("STATEMENT", "x")).toString();

    REQUIRE(result1 == "VARIABLE: x: 2, 3, 5, ");
    REQUIRE(result2 == "MODIFIES:STATEMENT: x: 5, 2, 3, ");
    REQUIRE(result3 == "USES:STATEMENT: x: 2, 3, ");*/

}