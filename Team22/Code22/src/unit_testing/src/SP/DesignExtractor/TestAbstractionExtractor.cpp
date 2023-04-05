#include "SP/DesignExtractor/AbstractionExtractor.h"
#include "catch.hpp"
using namespace std;
TEST_CASE("Testcase1_ExtractOneStatement_ShouldSuccess") {
    TNode variable1 = TNode(TokenType::NAME_IDENTIFIER, "x", 1, std::vector<TNode>(0));
    TNode read1 = TNode(TokenType::READ, "read", 1, std::vector<TNode>(0));
    std::vector<TNode> child2;
    child2.push_back(variable1);
    read1.children = child2;

    TNode stmtlist1 = TNode(TokenType::STATEMENT_LIST, "stmtList", 1, std::vector<TNode>(0));
    std::vector<TNode> child1;
    child1.push_back(read1);
    stmtlist1.children = child1;

    TNode root = TNode(TokenType::PROCEDURE, "main", 0, std::vector<TNode>(0));
    std::vector<TNode> child;
    child.push_back(stmtlist1);
    root.children = child;

    /*PKB pkbinstance = PKB();
    pkbinstance.clearAllDatabases();
    AbstractionExtractor abstractionExtractor;

    abstractionExtractor.extractAbstraction(root, pkbinstance, "procedure1");

    std::string result1 = pkbinstance.getDesignEntity("VARIABLE", "x").toString();
    std::string result2 = pkbinstance.getDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "x")).toString();
    REQUIRE(result1 == "VARIABLE: x: 1, ");
    REQUIRE(result2 == "MODIFIES:STATEMENT: x: 1, ");*/
}

TEST_CASE("Testcase2_ExtractFiveStatement_ShouldSuccess") {

    TNode variable4 = TNode(TokenType::NAME_IDENTIFIER, "y", 5, std::vector<TNode>(0));
    TNode read2 = TNode(TokenType::READ, "read", 5, std::vector<TNode>(0));
    std::vector<TNode> child8;
    child8.push_back(variable4);
    read2.children = child8;

    TNode variable3 = TNode(TokenType::NAME_IDENTIFIER, "x", 4, std::vector<TNode>(0));
    TNode print2 = TNode(TokenType::PRINT, "print", 4, std::vector<TNode>(0));
    std::vector<TNode> child7;
    child7.push_back(variable3);
    print2.children = child7;

    TNode stmtlist2 = TNode(TokenType::STATEMENT_LIST, "stmtList", 3, std::vector<TNode>(0));
    std::vector<TNode> child6;
    child6.push_back(print2);
    child6.push_back(read2);
    stmtlist2.children = child6;

    TNode condition1 = TNode(TokenType::OPERATOR, ">", 3, std::vector<TNode>(0));
    TNode variableInCondition = TNode(TokenType::NAME_IDENTIFIER, "y", 3, std::vector<TNode>(0));
    TNode constantInCondition = TNode(TokenType::INTEGER, "2", 3, std::vector<TNode>(0));
    std::vector<TNode> child5;
    child5.push_back(variableInCondition);
    child5.push_back(constantInCondition);
    condition1.children = child5;
    TNode while1 = TNode(TokenType::WHILE, "while", 3, std::vector<TNode>(0));
    std::vector<TNode> child4;
    child4.push_back(condition1);
    child4.push_back(stmtlist2);
    while1.children = child4;

    TNode variable2 = TNode(TokenType::NAME_IDENTIFIER, "y", 2, std::vector<TNode>(0));
    TNode print1 = TNode(TokenType::PRINT, "print", 2, std::vector<TNode>(0));
    std::vector<TNode> child3;
    child3.push_back(variable2);
    print1.children = child3;

    TNode variable1 = TNode(TokenType::NAME_IDENTIFIER, "x", 1, std::vector<TNode>(0));
    TNode read1 = TNode(TokenType::READ, "read", 1, std::vector<TNode>(0));
    std::vector<TNode> child2;
    child2.push_back(variable1);
    read1.children = child2;

    TNode stmtlist1 = TNode(TokenType::STATEMENT_LIST, "stmtList", 1, std::vector<TNode>(0));
    std::vector<TNode> child1;
    child1.push_back(read1);
    child1.push_back(print1);
    child1.push_back(while1);
    stmtlist1.children = child1;

    TNode root = TNode(TokenType::PROCEDURE, "main", 0, std::vector<TNode>(0));
    std::vector<TNode> child;
    child.push_back(stmtlist1);
    root.children = child;

    /*PKB pkbinstance = PKB();
    pkbinstance.clearAllDatabases();
    AbstractionExtractor abstractionExtractor;

    abstractionExtractor.extractAbstraction(root, pkbinstance, "procedure1");

    std::string result1 = pkbinstance.getDesignEntity("VARIABLE", "x").toString();
    std::string result2 = pkbinstance.getDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "x")).toString();
    std::string result3 = pkbinstance.getDesignAbstraction("USES", make_tuple("STATEMENT", "x")).toString();

    REQUIRE(result1 == "VARIABLE: x: 1, 4, ");
    REQUIRE(result2 == "MODIFIES:STATEMENT: x: 1, ");
    REQUIRE(result3 == "USES:STATEMENT: x: 4, 3, ");*/

}