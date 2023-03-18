#include "SP/DesignExtractor/StmtlstExtractor.h"
#include "catch.hpp"
using namespace std;

TEST_CASE("Testcase1_ExtractSimpleStatementlist_ShouldSuccess") {
    TNode variable2 = TNode(TokenType::NAME_IDENTIFIER, "y", 3, std::vector<TNode>(0));
    TNode read1 = TNode(TokenType::READ, "read", 3, std::vector<TNode>(0));
    std::vector<TNode> child2;
    child2.push_back(variable2);
    read1.children = child2;

    TNode variable1 = TNode(TokenType::NAME_IDENTIFIER, "y", 2, std::vector<TNode>(0));
    TNode print1 = TNode(TokenType::PRINT, "print", 2, std::vector<TNode>(0));
    std::vector<TNode> child1;
    child1.push_back(variable1);
    print1.children = child1;

    TNode stmtlist = TNode(TokenType::STATEMENT_LIST, "stmtList", 1, std::vector<TNode>(0));
    std::vector<TNode> child;
    child.push_back(print1);
    child.push_back(read1);
    stmtlist.children = child;

    PKB pkbinstance = PKB();
    pkbinstance.clearAllDatabases();
    StmtlstExtractor stmtlstExtractor;

    std::vector<int> ifContainers = std::vector<int>(0);
    ifContainers.push_back(1);
    std::vector<int> whileContainers = std::vector<int>(0);

    stmtlstExtractor.extractAbstraction(stmtlist, ifContainers, whileContainers, pkbinstance, 1, "procedure1");

    std::string result1 = pkbinstance.getDesignEntity("VARIABLE", "y").toString();
    std::string result2 = pkbinstance.getDesignAbstraction("USES", make_tuple("STATEMENT", "y")).toString();
    std::string result3 = pkbinstance.getDesignAbstraction("FOLLOWS", make_tuple("_", "2")).toString();
    std::string result4 = pkbinstance.getDesignAbstraction("FOLLOWSSTAR", make_tuple("_", "2")).toString();

    REQUIRE(result1 == "VARIABLE: y: 2, 3, ");
    REQUIRE(result2 == "USES:STATEMENT: y: 2, 1, ");
    REQUIRE(result3 == "FOLLOWS: 2: 3, ");
    REQUIRE(result4 == "FOLLOWSSTAR: 2: 3, ");

}

TEST_CASE("Testcase2_ExtractNestedStatementlist_ShouldSuccess") {
    TNode stmtlist2 = TNode(TokenType::STATEMENT_LIST, "stmtList", 3, std::vector<TNode>(0));

    TNode condition1 = TNode(TokenType::OPERATOR, ">", 3, std::vector<TNode>(0));
    TNode variable2 = TNode(TokenType::NAME_IDENTIFIER, "y", 3, std::vector<TNode>(0));
    TNode variable3 = TNode(TokenType::NAME_IDENTIFIER, "z", 3, std::vector<TNode>(0));
    std::vector<TNode> child4;
    child4.push_back(variable2);
    child4.push_back(variable3);
    condition1.children = child4;

    TNode variable1 = TNode(TokenType::NAME_IDENTIFIER, "y", 4, std::vector<TNode>(0));
    TNode read1 = TNode(TokenType::READ, "read", 4, std::vector<TNode>(0));
    std::vector<TNode> child3;
    child3.push_back(variable1);
    read1.children = child3;

    TNode stmtlist1 = TNode(TokenType::STATEMENT_LIST, "stmtList", 3, std::vector<TNode>(0));
    std::vector<TNode> child2;
    child2.push_back(read1);
    stmtlist1.children = child2;

    TNode ifNode = TNode(TokenType::IF, "if", 3, std::vector<TNode>(0));
    std::vector<TNode> child1;
    child1.push_back(condition1);
    child1.push_back(stmtlist1);
    child1.push_back(stmtlist2);
    ifNode.children = child1;

    TNode stmtlist = TNode(TokenType::STATEMENT_LIST, "stmtList", 2, std::vector<TNode>(0));
    std::vector<TNode> child;
    child.push_back(ifNode);
    stmtlist.children = child;

    PKB pkbinstance = PKB();
    pkbinstance.clearAllDatabases();
    StmtlstExtractor stmtlstExtractor;

    std::vector<int> ifContainers = std::vector<int>(0);
    std::vector<int> whileContainers = std::vector<int>(0);
    whileContainers.push_back(2);

    stmtlstExtractor.extractAbstraction(stmtlist, ifContainers, whileContainers, pkbinstance, 2, "procedure1");

    std::string result1 = pkbinstance.getDesignEntity("VARIABLE", "y").toString();
    std::string result2 = pkbinstance.getDesignAbstraction("PARENT", make_tuple("_", "2")).toString();
    std::string result3 = pkbinstance.getDesignAbstraction("PARENTSTAR", make_tuple("_", "2")).toString();

    REQUIRE(result1 == "VARIABLE: y: 3, 4, ");
    REQUIRE(result2 == "PARENT: 2: 3, ");
    REQUIRE(result3 == "PARENTSTAR: 2: 3, 4, ");

}