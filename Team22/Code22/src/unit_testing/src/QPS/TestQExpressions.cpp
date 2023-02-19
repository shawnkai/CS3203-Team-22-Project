//
// Created by Shawn Tan Jing Kai on 17/02/2023.
//



#include "QPS/Evaluator.h"
#include "QPS/Parser.h"
#include "PKB/PKB.h"
#include "catch.hpp"


using namespace std;

TEST_CASE("TestCase1_UsesSExpressionEvaluate_SingleStatement") {
    PKB pkb;
    pkb.addDesignEntity("VARIABLE", make_tuple("v1", "1"));
    UsesSExpression usesExp("1", "v1");
    vector<string> expected = { "1" };
    vector<string> actual = usesExp.evaluate(pkb);
    REQUIRE(actual == expected);
}

TEST_CASE("TestCase2_UsesSExpressionEvaluate_NoResults") {
    PKB pkb;
    pkb.addDesignEntity("VARIABLE", make_tuple("v1", "1"));
    UsesSExpression usesExp("2", "v1");
    vector<string> expected = {};
    vector<string> actual = usesExp.evaluate(pkb);
    REQUIRE(actual == expected);
}

