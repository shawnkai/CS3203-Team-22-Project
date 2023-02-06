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

    pkb.addDesignEntity("VARIABLE", make_tuple("v", "1"));
    pkb.addDesignEntity("VARIABLE", make_tuple("a", "2"));

    QueryEvaluator queryEvaluator(pkb);
    QueryParser queryParser;

    string declaration = "variable v;";
    string query = "Select v";

    queryParser.parse(declaration);

    SelectExpression *exp = queryParser.parse(query);

    ::printf("%s\n", queryEvaluator.evaluate(exp).c_str());
}