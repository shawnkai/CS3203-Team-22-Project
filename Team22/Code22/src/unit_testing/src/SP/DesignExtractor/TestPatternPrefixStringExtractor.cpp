//
// Created by Yi Zhang on 18/2/23.
//
#include "catch.hpp"
#include "SP/DesignExtractor/PatternPrefixStringExtractor.h"
using namespace std;

TEST_CASE("TestCase1_TestBaseCaseAssignmentToPrefix_ShouldSuccess") {
    TNode t1 = TNode(TokenType::OPERATOR, "+", 1, std::vector<TNode>(0));
    TNode t2 = TNode(TokenType::INTEGER, "2", 1, std::vector<TNode>(0));
    TNode t3 = TNode(TokenType::INTEGER, "2", 1, std::vector<TNode>(0));
    t1.children.push_back(t2);
    t1.children.push_back(t3);
    TNode t4 = TNode(TokenType::NAME_IDENTIFIER, "x", 1, std::vector<TNode>(0));
    TNode t0 = TNode(TokenType::ASSIGN, "=", 1, {t4, t1});
    PatternPrefixStringExtractor extractor;
    extractor.extractPrefixString(t0,PKB());

    PKB testPatternPrefixExtractorPkb = PKB();
    vector<AssignPattern*> result = testPatternPrefixExtractorPkb.getAllRightHandExpressions();
    unordered_map<string, string> result2 = testPatternPrefixExtractorPkb.getAllRightHandExpressionsOfAVariable("x");
    REQUIRE(result.size() > 0);
    REQUIRE(result2.find("1")->second=="+22");
}

TEST_CASE("TestCase2_TestComplexCaseAssignmentToPrefix_ShouldSuccess") {
    PKB anotherInstance = PKB();
    anotherInstance.clearAllDatabases();

    TNode t1 = TNode(TokenType::INTEGER, "1", 1, std::vector<TNode>(0));
    TNode t2 = TNode(TokenType::INTEGER, "2", 1, std::vector<TNode>(0));
    TNode t3 = TNode(TokenType::INTEGER, "2", 1, std::vector<TNode>(0));
    TNode t4 = TNode(TokenType::INTEGER, "3", 1, std::vector<TNode>(0));
    TNode t5 = TNode(TokenType::INTEGER, "5", 1, std::vector<TNode>(0));
    TNode t6 = TNode(TokenType::INTEGER, "7", 1, std::vector<TNode>(0));
    TNode t7 = TNode(TokenType::OPERATOR, "*", 1, std::vector<TNode>(0));
    TNode t8 = TNode(TokenType::OPERATOR, "+", 1, std::vector<TNode>(0));
    TNode t9 = TNode(TokenType::OPERATOR, "-", 1, std::vector<TNode>(0));
    TNode t10 = TNode(TokenType::OPERATOR, "%", 1, std::vector<TNode>(0));
    TNode t11 = TNode(TokenType::OPERATOR, "/", 1, std::vector<TNode>(0));
    TNode t12 = TNode(TokenType::NAME_IDENTIFIER, "x", 1, std::vector<TNode>(0));
    t7.children.push_back(t1);
    t7.children.push_back(t2);
    t8.children.push_back(t7);
    t8.children.push_back(t5);
    t9.children.push_back(t4);
    t9.children.push_back(t3);
    t10.children.push_back(t8);
    t10.children.push_back(t9);
    t11.children.push_back(t10);
    t11.children.push_back(t6);
    TNode t0 = TNode(TokenType::ASSIGN, "=", 1, {t12, t11});
    PatternPrefixStringExtractor extractor;
    extractor.extractPrefixString(t0,anotherInstance);

    vector<AssignPattern*> result = anotherInstance.getAllRightHandExpressions();
    unordered_map<string, string> result2 = anotherInstance.getAllRightHandExpressionsOfAVariable("x");
    REQUIRE(result.size() > 0);
    REQUIRE(result2.find("1")->second=="/%+*125-327");
}
