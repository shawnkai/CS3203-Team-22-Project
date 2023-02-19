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
