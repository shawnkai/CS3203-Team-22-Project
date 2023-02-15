//
// Created by Atin Sakkeer Hussain on 06/02/2023.
//

//
// Created by Atin Sakkeer Hussain on 04/02/2023.
//


#include "QPS/Evaluator.h"
#include "QPS/Parser.h"
#include "PKB/PKB.h"
#include "catch.hpp"


using namespace std;

TEST_CASE("Test Select Statement Evaluation") {
    PKB pkb;

    pkb.addDesignEntity("PROCEDURE", make_tuple("main", "1"));
    pkb.addDesignEntity("VARIABLE", make_tuple("v1", "2"));
    pkb.addDesignEntity("VARIABLE", make_tuple("v2", "2"));


    QueryEvaluator queryEvaluator(pkb);
    QueryParser queryParser;

    string declaration = "variable v; procedure p;";
    string query1 = "Select v";
    string query2 = "Select p";

    queryParser.parse(declaration);

    SelectExpression *exp1 = queryParser.parse(query1);
    SelectExpression *exp2 = queryParser.parse(query2);

    vector<string> res1 = queryEvaluator.evaluate(exp1);
    vector<string> res2 = queryEvaluator.evaluate(exp2);

    REQUIRE(count(res1.begin(), res1.end(), "v1"));
    REQUIRE(count(res1.begin(), res1.end(), "v2"));
    REQUIRE(count(res2.begin(), res2.end(), "main"));
}

TEST_CASE("Test Select such that Modifies Evaluation") {
    PKB pkb;

    pkb.addDesignEntity("VARIABLE", make_tuple("v3", "1"));
    pkb.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "v3", "1"));

    QueryEvaluator queryEvaluator(pkb);
    QueryParser queryParser;

    string declaration = "variable v; read r;";
    string query = "Select v such that Modifies(1, v)";

    queryParser.parse(declaration);

    SelectExpression *exp = queryParser.parse(query);

    vector<string> res = queryEvaluator.evaluate(exp);

    REQUIRE(count(res.begin(), res.end(), "v3"));
}

TEST_CASE("Test Select such that Uses Evaluation") {
    PKB pkb;

    pkb.addDesignEntity("VARIABLE", make_tuple("v4", "1"));
    pkb.addDesignAbstraction("USES", make_tuple("STATEMENT", "v4", "1"));

    QueryEvaluator queryEvaluator(pkb);
    QueryParser queryParser;

    string declaration = "variable v; read r;";
    string query = "Select v such that Uses(1, v)";

    queryParser.parse(declaration);

    SelectExpression *exp = queryParser.parse(query);

    vector<string> res = queryEvaluator.evaluate(exp);

    REQUIRE(count(res.begin(), res.end(), "v4"));
}

TEST_CASE("Test Select such that Uses and Modifies Evaluation") {
    PKB pkb;

    pkb.addDesignEntity("VARIABLE", make_tuple("v5", "1"));
    pkb.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "v5", "3"));
    pkb.addDesignAbstraction("USES", make_tuple("STATEMENT", "v5", "4"));

    QueryEvaluator queryEvaluator(pkb);
    QueryParser queryParser;

    string declaration = "variable v; read r;";
    string query = "Select v such that Uses(4, v) and Modifies(3, v)";

    queryParser.parse(declaration);

    SelectExpression *exp = queryParser.parse(query);

    vector<string> res = queryEvaluator.evaluate(exp);

    REQUIRE(count(res.begin(), res.end(), "v5"));
}