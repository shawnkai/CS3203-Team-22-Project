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

    PKB pkbinstance = PKB();
    AbstractionExtractor abstractionExtractor;

    abstractionExtractor.extractAbstraction(root, pkbinstance);

    std::string result1 = pkbinstance.getDesignEntity("VARIABLE", "x").toString();
    //std::string result2 = pkbinstance.getDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "x")).toString();
    REQUIRE(result1 == "VARIABLE: x: 1, ");
}