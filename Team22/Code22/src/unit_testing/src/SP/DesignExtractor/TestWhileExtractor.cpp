#include "SP/DesignExtractor/WhileExtractor.h"
#include "catch.hpp"
using namespace std;
TEST_CASE("Testcase1_ExtractOneWhileStatement_ShouldSuccess") {

    TNode condition1 = TNode(TokenType::OPERATOR, "<", 1, std::vector<TNode>(0));
    TNode variable2 = TNode(TokenType::NAME_IDENTIFIER, "y", 1, std::vector<TNode>(0));
    TNode variable3 = TNode(TokenType::NAME_IDENTIFIER, "z", 1, std::vector<TNode>(0));
    std::vector<TNode> child3;
    child3.push_back(variable2);
    child3.push_back(variable3);
    condition1.children = child3;

    TNode variable1 = TNode(TokenType::NAME_IDENTIFIER, "y", 2, std::vector<TNode>(0));
    TNode read1 = TNode(TokenType::READ, "read", 2, std::vector<TNode>(0));
    std::vector<TNode> child2;
    child2.push_back(variable1);
    read1.children = child2;

    TNode stmtlist1 = TNode(TokenType::STATEMENT_LIST, "stmtList", 1, std::vector<TNode>(0));
    std::vector<TNode> child1;
    child1.push_back(read1);
    stmtlist1.children = child1;

    TNode whileNode = TNode(TokenType::WHILE, "while", 1, std::vector<TNode>(0));
    std::vector<TNode> child;
    child.push_back(condition1);
    child.push_back(stmtlist1);
    whileNode.children = child;

    PKB pkbinstance = PKB();
    pkbinstance.clearAllDatabases();
    WhileExtractor whileExtractor;

    std::vector<int> ifContainers = std::vector<int>(0);
    std::vector<int> whileContainers = std::vector<int>(0);

    whileExtractor.extractAbstraction(whileNode, ifContainers, whileContainers, pkbinstance, "procedure1");

    std::string result1 = pkbinstance.getDesignEntity("VARIABLE", "y").toString();
    std::string result2 = pkbinstance.getDesignAbstraction("USES", make_tuple("STATEMENT", "y")).toString();
    REQUIRE(result1 == "VARIABLE: y: 1, 2, ");
    REQUIRE(result2 == "USES:STATEMENT: y: 1, ");
}

TEST_CASE("Testcase2_ExtractNestedWhileStatement_ShouldSuccess") {
    TNode variable8 = TNode(TokenType::NAME_IDENTIFIER, "y", 4, std::vector<TNode>(0));
    TNode read1 = TNode(TokenType::READ, "read", 4, std::vector<TNode>(0));
    std::vector<TNode> child9;
    child9.push_back(variable8);
    read1.children = child9;

    TNode condition3 = TNode(TokenType::OPERATOR, "<", 3, std::vector<TNode>(0));
    TNode variable6 = TNode(TokenType::NAME_IDENTIFIER, "y", 3, std::vector<TNode>(0));
    TNode variable7 = TNode(TokenType::NAME_IDENTIFIER, "z", 3, std::vector<TNode>(0));
    std::vector<TNode> child8;
    child8.push_back(variable6);
    child8.push_back(variable7);
    condition3.children = child8;

    TNode stmtlist3 = TNode(TokenType::STATEMENT_LIST, "stmtList", 3, std::vector<TNode>(0));
    std::vector<TNode> child7;
    child7.push_back(read1);
    stmtlist3.children = child7;

    TNode whileNode3 = TNode(TokenType::WHILE, "while", 3, std::vector<TNode>(0));
    std::vector<TNode> child6;
    child6.push_back(condition3);
    child6.push_back(stmtlist3);
    whileNode3.children = child6;

    TNode condition2 = TNode(TokenType::OPERATOR, "<", 2, std::vector<TNode>(0));
    TNode variable4 = TNode(TokenType::NAME_IDENTIFIER, "y", 2, std::vector<TNode>(0));
    TNode variable5 = TNode(TokenType::NAME_IDENTIFIER, "z", 2, std::vector<TNode>(0));
    std::vector<TNode> child5;
    child5.push_back(variable4);
    child5.push_back(variable5);
    condition2.children = child5;

    TNode stmtlist2 = TNode(TokenType::STATEMENT_LIST, "stmtList", 2, std::vector<TNode>(0));

    TNode whileNode2 = TNode(TokenType::WHILE, "while", 2, std::vector<TNode>(0));
    std::vector<TNode> child3;
    child3.push_back(condition2);
    child3.push_back(stmtlist2);
    whileNode2.children = child3;

    TNode condition1 = TNode(TokenType::OPERATOR, "<", 1, std::vector<TNode>(0));
    TNode variable2 = TNode(TokenType::NAME_IDENTIFIER, "y", 1, std::vector<TNode>(0));
    TNode variable3 = TNode(TokenType::NAME_IDENTIFIER, "z", 1, std::vector<TNode>(0));
    std::vector<TNode> child2;
    child2.push_back(variable2);
    child2.push_back(variable3);
    condition1.children = child2;

    TNode stmtlist1 = TNode(TokenType::STATEMENT_LIST, "stmtList", 1, std::vector<TNode>(0));

    TNode whileNode = TNode(TokenType::WHILE, "while", 1, std::vector<TNode>(0));
    std::vector<TNode> child;
    child.push_back(condition1);
    child.push_back(stmtlist1);
    whileNode.children = child;

    PKB pkbinstance = PKB();
    pkbinstance.clearAllDatabases();
    WhileExtractor whileExtractor;

    std::vector<int> ifContainers = std::vector<int>(0);
    std::vector<int> whileContainers = std::vector<int>(0);

    whileExtractor.extractAbstraction(whileNode, ifContainers, whileContainers, pkbinstance, "procedure1");

    std::string result1 = pkbinstance.getDesignEntity("VARIABLE", "y").toString();
    std::string result2 = pkbinstance.getDesignAbstraction("USES", make_tuple("STATEMENT", "y")).toString();
    REQUIRE(result1 == "VARIABLE: y: 1, ");
    REQUIRE(result2 == "USES:STATEMENT: y: 1, ");
}