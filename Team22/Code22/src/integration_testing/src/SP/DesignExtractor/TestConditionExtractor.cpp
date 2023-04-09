#include "SP/DesignExtractor/ConditionExtractor.h"
#include "catch.hpp"
using namespace std;
TEST_CASE("Testcase1_ExtractSimpleCondition_ShouldSuccess") {
    TNode variable2 = TNode(TokenType::NAME_IDENTIFIER, "x", 1, std::vector<TNode>(0));
    TNode variable3 = TNode(TokenType::NAME_IDENTIFIER, "z", 1, std::vector<TNode>(0));

    TNode operator1 = TNode(TokenType::OPERATOR, ">", 1, std::vector<TNode>(0));
    std::vector<TNode> child3;
    child3.push_back(variable2);
    child3.push_back(variable3);
    operator1.children = child3;

    TNode variable1 = TNode(TokenType::NAME_IDENTIFIER, "x", 2, std::vector<TNode>(0));
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
    child.push_back(operator1);
    child.push_back(stmtlist1);
    whileNode.children = child;

    PKB pkbinstance = PKB();
    pkbinstance.clearAllDatabases("CalledForTestingPurposes");
    ConditionExtractor conditionExtractor;

    std::vector<string> ifContainers = std::vector<string>(0);
    ifContainers.push_back(std::to_string(1));
    std::vector<string> whileContainers = std::vector<string>(0);

    conditionExtractor.extractConditionAbstraction(operator1, ifContainers, whileContainers, pkbinstance, "procedure1", whileNode);

    std::string result1 = pkbinstance.getDesignEntity("VARIABLE", "x").toString();
    std::string result2 = pkbinstance.getDesignAbstraction("USES", make_tuple("STATEMENT", "x")).toString();
    std::string result3 = pkbinstance.getDesignAbstraction("USES", make_tuple("STATEMENT", "z")).toString();
    bool result4 = pkbinstance.isVariableUsedInPattern("WHILE", "1", "x");
    REQUIRE(result1 == "VARIABLE: x: 1, ");
    REQUIRE(result2 == "USES:STATEMENT: x: 1, ");
    REQUIRE(result3 == "USES:STATEMENT: z: 1, ");
    REQUIRE(result4);
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

    TNode variable4 = TNode(TokenType::NAME_IDENTIFIER, "z", 3, std::vector<TNode>(0));
    TNode read1 = TNode(TokenType::READ, "read", 3, std::vector<TNode>(0));
    std::vector<TNode> child4;
    child4.push_back(variable4);
    read1.children = child4;

    TNode stmtlist2 = TNode(TokenType::STATEMENT_LIST, "stmtList", 1, std::vector<TNode>(0));
    std::vector<TNode> child5;
    child5.push_back(read1);
    stmtlist2.children = child5;

    TNode variable5 = TNode(TokenType::NAME_IDENTIFIER, "y", 2, std::vector<TNode>(0));
    TNode print1 = TNode(TokenType::PRINT, "print", 2, std::vector<TNode>(0));
    std::vector<TNode> child6;
    child6.push_back(variable5);
    print1.children = child6;

    TNode stmtlist1 = TNode(TokenType::STATEMENT_LIST, "stmtList", 1, std::vector<TNode>(0));
    std::vector<TNode> child7;
    child7.push_back(print1);
    stmtlist1.children = child7;

    TNode ifNode = TNode(TokenType::IF, "if", 1, std::vector<TNode>(0));
    std::vector<TNode> child8;
    child8.push_back(operator1);
    child8.push_back(stmtlist1);
    child8.push_back(stmtlist2);
    ifNode.children = child8;

    PKB pkbinstance = PKB();
    pkbinstance.clearAllDatabases("CalledForTestingPurposes");
    ConditionExtractor conditionExtractor;

    std::vector<string> ifContainers = std::vector<string>(0);
    ifContainers.push_back(std::to_string(2));
    ifContainers.push_back(std::to_string(3));

    std::vector<string> whileContainers = std::vector<string>(0);
    whileContainers.push_back(std::to_string(1));

    conditionExtractor.extractConditionAbstraction(operator1, ifContainers, whileContainers, pkbinstance, "procedure1", ifNode);


    std::string result1 = pkbinstance.getDesignEntity("VARIABLE", "x").toString();
    std::string result2 = pkbinstance.getDesignAbstraction("USES", make_tuple("STATEMENT", "y")).toString();
    std::string result3 = pkbinstance.getDesignAbstraction("USES", make_tuple("STATEMENT", "z")).toString();
    std::string result4 = pkbinstance.getDesignAbstraction("USES", make_tuple("STATEMENT", "x")).toString();
    bool result5 = pkbinstance.isVariableUsedInPattern("IF", "3", "z");
    REQUIRE(result1 == "VARIABLE: x: 3, ");
    REQUIRE(result2 == "USES:STATEMENT: y: 3, 1, 2, ");
    REQUIRE(result3 == "USES:STATEMENT: z: 3, 1, 2, ");
    REQUIRE(result4 == "USES:STATEMENT: x: 3, 1, 2, ");
    REQUIRE(result5);
}