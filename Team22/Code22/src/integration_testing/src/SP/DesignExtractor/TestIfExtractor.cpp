#include "SP/DesignExtractor/IfExtractor.h"
#include "catch.hpp"
using namespace std;
TEST_CASE("Testcase1_ExtractOneIfStatement_ShouldSuccess") {

    TNode variable4 = TNode(TokenType::NAME_IDENTIFIER, "y", 3, std::vector<TNode>(0));
    TNode print1 = TNode(TokenType::PRINT, "print", 3, std::vector<TNode>(0));
    std::vector<TNode> child5;
    child5.push_back(variable4);
    print1.children = child5;

    TNode stmtlist2 = TNode(TokenType::STATEMENT_LIST, "stmtList", 1, std::vector<TNode>(0));
    std::vector<TNode> child4;
    child4.push_back(print1);
    stmtlist2.children = child4;

    TNode condition1 = TNode(TokenType::OPERATOR, "<", 1, std::vector<TNode>(0));
    TNode variable2 = TNode(TokenType::NAME_IDENTIFIER, "y", 1, std::vector<TNode>(0));
    TNode variable3 = TNode(TokenType::NAME_IDENTIFIER, "x", 1, std::vector<TNode>(0));
    std::vector<TNode> child3;
    child3.push_back(variable2);
    child3.push_back(variable3);
    condition1.children = child3;

    TNode variable1 = TNode(TokenType::NAME_IDENTIFIER, "x", 2, std::vector<TNode>(0));
    TNode read1 = TNode(TokenType::READ, "read", 2, std::vector<TNode>(0));
    std::vector<TNode> child2;
    child2.push_back(variable1);
    read1.children = child2;

    TNode stmtlist1 = TNode(TokenType::STATEMENT_LIST, "stmtList", 1, std::vector<TNode>(0));
    std::vector<TNode> child1;
    child1.push_back(read1);
    stmtlist1.children = child1;

    TNode ifNode = TNode(TokenType::IF, "if", 1, std::vector<TNode>(0));
    std::vector<TNode> child;
    child.push_back(condition1);
    child.push_back(stmtlist1);
    child.push_back(stmtlist2);
    ifNode.children = child;

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
    auto ifExtractor = factory1.createExtractor(ifNode, newmap, pkbinstance);
    ifExtractor->extractAbstraction();

    std::string result1 = pkbinstance.getDesignEntity("VARIABLE", "x").toString();
    std::string result2 = pkbinstance.getDesignAbstraction("USES", make_tuple("STATEMENT", "y")).toString();
    REQUIRE(result1 == "VARIABLE: x: 1, 2, ");
    REQUIRE(result2 == "USES:STATEMENT: y: 1, 3, ");
}

TEST_CASE("Testcase2_ExtractNestedIfStatement_ShouldSuccess") {

    TNode variable8 = TNode(TokenType::NAME_IDENTIFIER, "y", 4, std::vector<TNode>(0));
    TNode print1 = TNode(TokenType::PRINT, "print", 4, std::vector<TNode>(0));
    std::vector<TNode> child9;
    child9.push_back(variable8);
    print1.children = child9;

    TNode stmtlist6 = TNode(TokenType::STATEMENT_LIST, "stmtList", 3, std::vector<TNode>(0));

    TNode stmtlist5 = TNode(TokenType::STATEMENT_LIST, "stmtList", 3, std::vector<TNode>(0));
    std::vector<TNode> child8;
    child8.push_back(print1);
    stmtlist5.children = child8;

    TNode condition3 = TNode(TokenType::OPERATOR, ">", 3, std::vector<TNode>(0));
    TNode variable6 = TNode(TokenType::NAME_IDENTIFIER, "x", 3, std::vector<TNode>(0));
    TNode variable7 = TNode(TokenType::NAME_IDENTIFIER, "y", 3, std::vector<TNode>(0));
    std::vector<TNode> child7;
    child7.push_back(variable6);
    child7.push_back(variable7);
    condition3.children = child7;

    TNode ifNode3 = TNode(TokenType::IF, "if", 3, std::vector<TNode>(0));
    std::vector<TNode> child6;
    child6.push_back(condition3);
    child6.push_back(stmtlist5);
    child6.push_back(stmtlist6);
    ifNode3.children = child6;

    TNode stmtlist4 = TNode(TokenType::STATEMENT_LIST, "stmtList", 2, std::vector<TNode>(0));

    TNode stmtlist3 = TNode(TokenType::STATEMENT_LIST, "stmtList", 2, std::vector<TNode>(0));
    std::vector<TNode> child5;
    child5.push_back(ifNode3);
    stmtlist3.children = child5;

    TNode condition2 = TNode(TokenType::OPERATOR, ">", 2, std::vector<TNode>(0));
    TNode variable4 = TNode(TokenType::NAME_IDENTIFIER, "x", 2, std::vector<TNode>(0));
    TNode variable5 = TNode(TokenType::NAME_IDENTIFIER, "z", 2, std::vector<TNode>(0));
    std::vector<TNode> child4;
    child4.push_back(variable4);
    child4.push_back(variable5);
    condition2.children = child4;

    TNode ifNode2 = TNode(TokenType::IF, "if", 2, std::vector<TNode>(0));
    std::vector<TNode> child3;
    child3.push_back(condition2);
    child3.push_back(stmtlist3);
    child3.push_back(stmtlist4);
    ifNode2.children = child3;

    TNode stmtlist2 = TNode(TokenType::STATEMENT_LIST, "stmtList", 1, std::vector<TNode>(0));

    TNode condition1 = TNode(TokenType::OPERATOR, "<", 1, std::vector<TNode>(0));
    TNode variable2 = TNode(TokenType::NAME_IDENTIFIER, "X", 1, std::vector<TNode>(0));
    TNode variable3 = TNode(TokenType::NAME_IDENTIFIER, "y", 1, std::vector<TNode>(0));
    std::vector<TNode> child2;
    child2.push_back(variable2);
    child2.push_back(variable3);
    condition1.children = child2;

    TNode stmtlist1 = TNode(TokenType::STATEMENT_LIST, "stmtList", 1, std::vector<TNode>(0));
    std::vector<TNode> child1;
    child1.push_back(ifNode2);
    stmtlist1.children = child1;

    TNode ifNode = TNode(TokenType::IF, "if", 1, std::vector<TNode>(0));
    std::vector<TNode> child;
    child.push_back(condition1);
    child.push_back(stmtlist1);
    child.push_back(stmtlist2);
    ifNode.children = child;

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
    auto ifExtractor = factory1.createExtractor(ifNode, newmap, pkbinstance);
    ifExtractor->extractAbstraction();

    std::string result1 = pkbinstance.getDesignEntity("VARIABLE", "x").toString();
    std::string result2 = pkbinstance.getDesignAbstraction("USES", make_tuple("STATEMENT", "y")).toString();
    REQUIRE(result1 == "VARIABLE: x: 2, 3, ");
    REQUIRE(result2 == "USES:STATEMENT: y: 1, 3, 2, 4, ");
}
