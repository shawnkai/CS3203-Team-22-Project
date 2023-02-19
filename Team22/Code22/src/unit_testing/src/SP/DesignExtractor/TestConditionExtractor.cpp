#include "SP/DesignExtractor/ConditionExtractor.h"
#include "catch.hpp"
using namespace std;
TEST_CASE("Testcase1_ExtractSimpleCondition_ShouldSuccess") {
    TNode variable1 = TNode(TokenType::NAME_IDENTIFIER, "x", 1, std::vector<TNode>(0));
    TNode variable2 = TNode(TokenType::NAME_IDENTIFIER, "z", 1, std::vector<TNode>(0));

    TNode operator1 = TNode(TokenType::OPERATOR, ">", 1, std::vector<TNode>(0));
    std::vector<TNode> child;
    child.push_back(variable1);
    child.push_back(variable2);
    operator1.children = child;

    PKB pkbinstance = PKB();
    pkbinstance.clearAllDatabases();
    ConditionExtractor conditionExtractor;

    std::vector<int> ifContainers = std::vector<int>(0);
    ifContainers.push_back(1);
    std::vector<int> whileContainers = std::vector<int>(0);

    conditionExtractor.extractAbstraction(operator1, ifContainers, whileContainers, pkbinstance);

    std::string result1 = pkbinstance.getDesignEntity("VARIABLE", "x").toString();
    std::string result2 = pkbinstance.getDesignAbstraction("USES", make_tuple("STATEMENT", "x")).toString();
    std::string result3 = pkbinstance.getDesignAbstraction("USES", make_tuple("STATEMENT", "z")).toString();
    REQUIRE(result1 == "VARIABLE: x: 1, ");
    REQUIRE(result2 == "USES:STATEMENT: x: 1, ");
    REQUIRE(result3 == "USES:STATEMENT: z: 1,");
}

TEST_CASE("Testcase2_ExtractComplexCondition_ShouldSuccess") {
    TNode variable3 = TNode(TokenType::NAME_IDENTIFIER, "z", 3, std::vector<TNode>(0));
    TNode constant2 = TNode(TokenType::INTEGER, "2", 3, std::vector<TNode>(0));

    TNode operator4 = TNode(TokenType::OPERATOR, "-", 3, std::vector<TNode>(0));
    std::vector<TNode> child3;
    child3.push_back(variable3);
    child3.push_back(constant2);
    operator4.children = child3;


    TNode variable2 = TNode(TokenType::NAME_IDENTIFIER, "y", 3, std::vector<TNode>(0));
    TNode constant1 = TNode(TokenType::INTEGER, "5", 3, std::vector<TNode>(0));

    TNode operator3 = TNode(TokenType::OPERATOR, "+", 3, std::vector<TNode>(0));
    std::vector<TNode> child2;
    child2.push_back(variable2);
    child2.push_back(constant1);
    operator3.children = child2;

    TNode operator2 = TNode(TokenType::OPERATOR, "*", 3, std::vector<TNode>(0));
    std::vector<TNode> child1;
    child1.push_back(operator3);
    child1.push_back(operator4);
    operator2.children = child1;

    TNode variable1 = TNode(TokenType::NAME_IDENTIFIER, "x", 3, std::vector<TNode>(0));

    TNode operator1 = TNode(TokenType::OPERATOR, "<", 3, std::vector<TNode>(0));
    std::vector<TNode> child;
    child.push_back(variable1);
    child.push_back(operator2);
    operator1.children = child;

    PKB pkbinstance = PKB();
    pkbinstance.clearAllDatabases();
    ConditionExtractor conditionExtractor;

    std::vector<int> ifContainers = std::vector<int>(0);
    ifContainers.push_back(2);
    ifContainers.push_back(3);
    std::vector<int> whileContainers = std::vector<int>(0);
    whileContainers.push_back(1);

    conditionExtractor.extractAbstraction(operator1, ifContainers, whileContainers, pkbinstance);

    std::string result1 = pkbinstance.getDesignEntity("VARIABLE", "x").toString();
    std::string result2 = pkbinstance.getDesignAbstraction("USES", make_tuple("STATEMENT", "y")).toString();
    std::string result3 = pkbinstance.getDesignAbstraction("USES", make_tuple("STATEMENT", "z")).toString();
    std::string result4 = pkbinstance.getDesignAbstraction("USES", make_tuple("STATEMENT", "x")).toString();
    REQUIRE(result1 == "VARIABLE: x: 1, ");
    REQUIRE(result2 == "USES:STATEMENT: y: 1, ");
    REQUIRE(result3 == "USES:STATEMENT: z: 1, ");
    REQUIRE(result4 == "USES:STATEMENT: x: 1, ");

}