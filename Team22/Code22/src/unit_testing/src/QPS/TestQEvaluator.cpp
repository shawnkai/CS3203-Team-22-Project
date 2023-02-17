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

    REQUIRE(queryEvaluator.evaluate(exp1).find("v1") != string::npos);
    REQUIRE(queryEvaluator.evaluate(exp2).find("main") != string::npos);
}

TEST_CASE("Test Select such that Modifies Evaluation") {
    PKB pkb;

    pkb.addDesignEntity("VARIABLE", make_tuple("v", "1"));
    pkb.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "v", "1"));

    QueryEvaluator queryEvaluator(pkb);
    QueryParser queryParser;

    string declaration = "variable v; read r;";
    string query = "Select v such that Modifies(1, v)";

    queryParser.parse(declaration);

    SelectExpression *exp = queryParser.parse(query);

    REQUIRE(queryEvaluator.evaluate(exp).find('v') != string::npos);
}