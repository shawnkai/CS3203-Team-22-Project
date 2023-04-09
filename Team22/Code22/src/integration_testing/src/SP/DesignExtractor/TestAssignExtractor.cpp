#include "SP/DesignExtractor/AssignExtractor.h"
#include "catch.hpp"
using namespace std;
TEST_CASE("Testcase1_ExtractSimpleAssignment_ShouldSuccess") {
    TNode variable1 = TNode(TokenType::NAME_IDENTIFIER, "y", 1, std::vector<TNode>(0));
    TNode constant1 = TNode(TokenType::INTEGER, "5", 1, std::vector<TNode>(0));

    TNode operator1 = TNode(TokenType::OPERATOR, "+", 1, std::vector<TNode>(0));
    std::vector<TNode> child2;
    child2.push_back(variable1);
    child2.push_back(constant1);
    operator1.children = child2;

    TNode variableLhs = TNode(TokenType::NAME_IDENTIFIER, "x", 1, std::vector<TNode>(0));

    TNode assignNode = TNode(TokenType::ASSIGN, "assign", 1, std::vector<TNode>(0));
    std::vector<TNode> child;
    child.push_back(variableLhs);
    child.push_back(operator1);
    assignNode.children = child;

    PKB pkbinstance = PKB();
    pkbinstance.clearAllDatabases("CalledForTestingPurposes");

    ExtractorFactory factory1;
    std::vector<string> ifContainer = std::vector<string>(0);
    std::vector<string> whileContainer = std::vector<string>(0);
    std::map<string, vector<string>> newmap;
    newmap["IfContainer"] = ifContainer;
    newmap["whileContainer"] = whileContainer;
    vector<string> vector1;
    vector1.push_back("procedure1");
    newmap["procedureName"] = vector1;
    vector<string> vector3;
    vector3.push_back(std::to_string(0));
    newmap["containerLineNo"] = vector3;
    auto assignExtractor = factory1.createExtractor(assignNode, newmap, pkbinstance);
    assignExtractor->extractAbstraction();

    std::string result1 = pkbinstance.getDesignEntity("VARIABLE", "x").toString();
    std::string result2 = pkbinstance.getDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "x")).toString();
    std::string result3 = pkbinstance.getDesignAbstraction("USES", make_tuple("STATEMENT", "y")).toString();
    REQUIRE(result1 == "VARIABLE: x: 1, ");
    REQUIRE(result2 == "MODIFIES:STATEMENT: x: 1, ");
    REQUIRE(result3 == "USES:STATEMENT: y: 1, ");
}

TEST_CASE("Testcase2_ExtractComplexAssignment_ShouldSuccess") {
    TNode variable3 = TNode(TokenType::NAME_IDENTIFIER, "a", 3, std::vector<TNode>(0));
    TNode variable4 = TNode(TokenType::INTEGER, "3", 3, std::vector<TNode>(0));

    TNode operator4 = TNode(TokenType::OPERATOR, "+", 3, std::vector<TNode>(0));
    std::vector<TNode> child5;
    child5.push_back(variable3);
    child5.push_back(variable4);
    operator4.children = child5;

    TNode variable1 = TNode(TokenType::NAME_IDENTIFIER, "y", 3, std::vector<TNode>(0));
    TNode variable2 = TNode(TokenType::NAME_IDENTIFIER, "z", 3, std::vector<TNode>(0));

    TNode operator3 = TNode(TokenType::OPERATOR, "-", 3, std::vector<TNode>(0));
    std::vector<TNode> child4;
    child4.push_back(variable1);
    child4.push_back(variable2);
    operator3.children = child4;

    TNode constant1 = TNode(TokenType::INTEGER, "5", 3, std::vector<TNode>(0));

    TNode operator2 = TNode(TokenType::OPERATOR, "*", 3, std::vector<TNode>(0));
    std::vector<TNode> child3;
    child3.push_back(operator3);
    child3.push_back(constant1);
    operator2.children = child3;

    TNode operator1 = TNode(TokenType::OPERATOR, "+", 3, std::vector<TNode>(0));
    std::vector<TNode> child2;
    child2.push_back(operator2);
    child2.push_back(operator4);
    operator1.children = child2;

    TNode variableLhs = TNode(TokenType::NAME_IDENTIFIER, "x", 3, std::vector<TNode>(0));

    TNode assignNode = TNode(TokenType::ASSIGN, "assign", 3, std::vector<TNode>(0));
    std::vector<TNode> child;
    child.push_back(variableLhs);
    child.push_back(operator1);
    assignNode.children = child;

    PKB pkbinstance = PKB();
    pkbinstance.clearAllDatabases("CalledForTestingPurposes");

    ExtractorFactory factory1;
    std::vector<string> ifContainer = std::vector<string>(0);
    std::vector<string> whileContainer = std::vector<string>(0);
    ifContainer.push_back(std::to_string(2));
    whileContainer.push_back(std::to_string(1));
    std::map<string, vector<string>> newmap;
    newmap["IfContainer"] = ifContainer;
    newmap["whileContainer"] = whileContainer;
    vector<string> vector1;
    vector1.push_back("procedure1");
    newmap["procedureName"] = vector1;
    vector<string> vector3;
    vector3.push_back(std::to_string(0));
    newmap["containerLineNo"] = vector3;
    auto assignExtractor = factory1.createExtractor(assignNode, newmap, pkbinstance);
    assignExtractor->extractAbstraction();

    std::string result1 = pkbinstance.getDesignEntity("VARIABLE", "y").toString();
    std::string result2 = pkbinstance.getDesignEntity("CONSTANT", "3").toString();
    std::string result3 = pkbinstance.getDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "x")).toString();
    std::string result4 = pkbinstance.getDesignAbstraction("USES", make_tuple("STATEMENT", "z")).toString();
    REQUIRE(result1 == "VARIABLE: y: 3, ");
    REQUIRE(result2 == "CONSTANT: 3: 3, ");
    REQUIRE(result3 == "MODIFIES:STATEMENT: x: 3, 1, 2, ");
    REQUIRE(result4 == "USES:STATEMENT: z: 3, 1, 2, ");
}