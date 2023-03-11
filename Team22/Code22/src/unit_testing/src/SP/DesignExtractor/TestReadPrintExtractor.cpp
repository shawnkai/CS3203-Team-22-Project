#include "SP/DesignExtractor/ReadPrintExtractor.h"
#include "catch.hpp"
using namespace std;
TEST_CASE("Testcase1_ExtractPrintStatement_ShouldSuccess") {

    TNode variable = TNode(TokenType::NAME_IDENTIFIER, "y", 2, std::vector<TNode>(0));
    TNode print1 = TNode(TokenType::PRINT, "print", 2, std::vector<TNode>(0));
    std::vector<TNode> child;
    child.push_back(variable);
    print1.children = child;

    PKB pkbinstance = PKB();
    pkbinstance.clearAllDatabases();
    ReadPrintExtractor readPrintExtractor;

    std::vector<int> ifContainers = std::vector<int>(0);
    ifContainers.push_back(1);
    std::vector<int> whileContainers = std::vector<int>(0);

    readPrintExtractor.extractAbstraction(print1, ifContainers, whileContainers, pkbinstance, "procedure1");

    std::string result1 = pkbinstance.getDesignEntity("VARIABLE", "y").toString();
    std::string result2 = pkbinstance.getDesignAbstraction("USES", make_tuple("STATEMENT", "y")).toString();
    REQUIRE(result1 == "VARIABLE: y: 2, ");
    REQUIRE(result2 == "USES:STATEMENT: y: 2, 1, ");
}

TEST_CASE("Testcase1_ExtractReadStatement_ShouldSuccess") {

    TNode variable = TNode(TokenType::NAME_IDENTIFIER, "y", 2, std::vector<TNode>(0));
    TNode read1 = TNode(TokenType::READ, "read", 2, std::vector<TNode>(0));
    std::vector<TNode> child;
    child.push_back(variable);
    read1.children = child;

    PKB pkbinstance = PKB();
    pkbinstance.clearAllDatabases();
    ReadPrintExtractor readPrintExtractor;

    std::vector<int> ifContainers = std::vector<int>(0);
    ifContainers.push_back(1);
    std::vector<int> whileContainers = std::vector<int>(0);

    readPrintExtractor.extractAbstraction(read1, ifContainers, whileContainers, pkbinstance, "procedure1");

    std::string result1 = pkbinstance.getDesignEntity("VARIABLE", "y").toString();
    std::string result2 = pkbinstance.getDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "y")).toString();
    REQUIRE(result1 == "VARIABLE: y: 2, ");
    REQUIRE(result2 == "MODIFIES:STATEMENT: y: 2, 1, ");
}