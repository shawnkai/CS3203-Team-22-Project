#include "SP/DesignExtractor/ReadPrintExtractor.h"
#include "SP/DesignExtractor/ExtractorFactory.h"
#include "catch.hpp"
using namespace std;
TEST_CASE("Testcase1_ExtractPrintStatement_ShouldSuccess") {

    TNode variable = TNode(TokenType::NAME_IDENTIFIER, "y", 2, std::vector<TNode>(0));
    TNode print1 = TNode(TokenType::PRINT, "print", 2, std::vector<TNode>(0));
    std::vector<TNode> child;
    child.push_back(variable);
    print1.children = child;

    PKB pkbinstance = PKB();
    pkbinstance.clearAllDatabases("CalledForTestingPurposes");

    ExtractorFactory factory1;
    std::vector<string> ifContainer = std::vector<string>(0);
    ifContainer.push_back(std::to_string(1));
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
    auto readPrintExtractor = factory1.createExtractor(print1, newmap, pkbinstance);
    readPrintExtractor->extractAbstraction();

    std::string result1 = pkbinstance.getDesignEntity("VARIABLE", "y").toString();
    std::string result2 = pkbinstance.getDesignAbstraction("USES", make_tuple("STATEMENT", "y")).toString();
    REQUIRE(result1 == "VARIABLE: y: 2, ");
    REQUIRE(result2 == "USES:STATEMENT: y: 2, 1, ");
}

TEST_CASE("Testcase2_ExtractReadStatement_ShouldSuccess") {

    TNode variable = TNode(TokenType::NAME_IDENTIFIER, "y", 2, std::vector<TNode>(0));
    TNode read1 = TNode(TokenType::READ, "read", 2, std::vector<TNode>(0));
    std::vector<TNode> child;
    child.push_back(variable);
    read1.children = child;

    PKB pkbinstance = PKB();
    pkbinstance.clearAllDatabases("CalledForTestingPurposes");

    ExtractorFactory factory1;
    std::vector<string> ifContainer = std::vector<string>(0);
    ifContainer.push_back(std::to_string(1));
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
    auto readPrintExtractor = factory1.createExtractor(read1, newmap, pkbinstance);
    readPrintExtractor->extractAbstraction();

    std::string result1 = pkbinstance.getDesignEntity("VARIABLE", "y").toString();
    std::string result2 = pkbinstance.getDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "y")).toString();
    REQUIRE(result1 == "VARIABLE: y: 2, ");
    REQUIRE(result2 == "MODIFIES:STATEMENT: y: 2, 1, ");
}