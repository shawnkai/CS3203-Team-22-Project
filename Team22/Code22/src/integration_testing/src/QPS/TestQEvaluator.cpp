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
#include "Utilities.h"


using namespace std;

TEST_CASE("TestCase1_EvaluateSelectStatement_ShouldSuccess") {
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

    REQUIRE(Utilities::checkIfPresent(res1, "v1"));
    REQUIRE(Utilities::checkIfPresent(res1, "v2"));
    REQUIRE(Utilities::checkIfPresent(res2, "main"));
}

TEST_CASE("TestCase2_EvaluateSelectStatementWithSuchThatModifies_ShouldSuccess") {
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

    REQUIRE(Utilities::checkIfPresent(res, "v3"));
}

TEST_CASE("TestCase4_EvaluateSelectStatementWithSuchThatUses_ShouldSuccess") {
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

    REQUIRE(Utilities::checkIfPresent(res, "v4"));
}

TEST_CASE("TestCase5_EvaluateSelectStatementWithPatternExactMatching_ShouldSuccess") {
    PKB pkb;

    pkb.addDesignEntity("VARIABLE", make_tuple("v6", "8"));
    pkb.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "v6", "8"));
    pkb.addDesignAbstraction("USES", make_tuple("STATEMENT", "v7", "8"));
    pkb.addDesignAbstraction("USES", make_tuple("STATEMENT", "v8", "8"));
    pkb.addAssignPattern("v6", Utilities::infixToPrefix("v7+v8"), "8");

    QueryEvaluator queryEvaluator(pkb);
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query = "Select a such that pattern a(_, \"v7+v8\")";

    queryParser.parse(declaration);

    SelectExpression *exp = queryParser.parse(query);

    vector<string> res = queryEvaluator.evaluate(exp);

    REQUIRE(Utilities::checkIfPresent(res, "8"));
}

TEST_CASE("TestCase6_EvaluateSelectStatementWithPatternWildCard_ShouldSuccess") {
    PKB pkb;

    pkb.addDesignEntity("VARIABLE", make_tuple("v6", "9"));
    pkb.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "v6", "9"));
    pkb.addDesignAbstraction("USES", make_tuple("STATEMENT", "v7", "9"));
    pkb.addDesignAbstraction("USES", make_tuple("STATEMENT", "v8", "9"));
    pkb.addDesignAbstraction("USES", make_tuple("STATEMENT", "v9", "9"));
    pkb.addAssignPattern("v6", Utilities::infixToPrefix("(v7+v8)*(v7+v9)"), "9");

    QueryEvaluator queryEvaluator(pkb);
    QueryParser queryParser;

    string declaration = "variable v; assign a;";
    string query1 = "Select a such that pattern a(_, _\"v7+v8\"_)";
    string query2 = "Select a such that pattern a(_, _\"v7+v9\"_)";

    queryParser.parse(declaration);

    SelectExpression *exp1 = queryParser.parse(query1);
    SelectExpression *exp2 = queryParser.parse(query2);

    vector<string> res1 = queryEvaluator.evaluate(exp1);
    vector<string> res2 = queryEvaluator.evaluate(exp2);

    REQUIRE(Utilities::checkIfPresent(res1, "9"));
    REQUIRE(Utilities::checkIfPresent(res2, "9"));
}

TEST_CASE("TestCase7_EvaluateSelectStatementWithSuchThatFollows_ShouldSuccess") {
    PKB pkb;

    pkb.addDesignEntity("ASSIGNMENT", make_tuple("ASSIGNMENT", "10"));
    pkb.addDesignEntity("ASSIGNMENT", make_tuple("ASSIGNMENT", "11"));
    pkb.addDesignAbstraction("FOLLOWS", make_tuple("_", "10", "11"));

    QueryEvaluator queryEvaluator(pkb);
    QueryParser queryParser;

    string declaration = "assign a;";
    string query1 = "Select a such that Follows(a, 11)";
    string query2 = "Select a such that Follows(10, a)";

    queryParser.parse(declaration);

    SelectExpression *exp1 = queryParser.parse(query1);
    SelectExpression *exp2 = queryParser.parse(query2);

    vector<string> res1 = queryEvaluator.evaluate(exp1);
    vector<string> res2 = queryEvaluator.evaluate(exp2);

    REQUIRE(Utilities::checkIfPresent(res1, "10"));
    REQUIRE(Utilities::checkIfPresent(res2, "11"));
}

TEST_CASE("TestCase8_EvaluateSelectStatementWithSuchThatFollowsSynonyms_ShouldSuccess") {
    PKB pkb;

    pkb.addDesignEntity("ASSIGNMENT", make_tuple("ASSIGNMENT", "12"));
    pkb.addDesignEntity("WHILE", make_tuple("WHILE", "13"));
    pkb.addDesignAbstraction("FOLLOWS", make_tuple("_", "12", "13"));

    QueryEvaluator queryEvaluator(pkb);
    QueryParser queryParser;

    string declaration = "assign a; while w;";
    string query1 = "Select a such that Follows(a, w)";
    string query2 = "Select w such that Follows(a, w)";

    queryParser.parse(declaration);

    SelectExpression *exp1 = queryParser.parse(query1);
    SelectExpression *exp2 = queryParser.parse(query2);

    vector<string> res1 = queryEvaluator.evaluate(exp1);
    vector<string> res2 = queryEvaluator.evaluate(exp2);

    REQUIRE(Utilities::checkIfPresent(res1, "12"));
    REQUIRE(Utilities::checkIfPresent(res2, "13"));
}

TEST_CASE("TestCase9_EvaluateSelectStatementWithSuchThatParent_ShouldSuccess") {
    PKB pkb;

    pkb.addDesignEntity("ASSIGNMENT", make_tuple("ASSIGNMENT", "15"));
    pkb.addDesignEntity("WHILE", make_tuple("WHILE", "14"));
    pkb.addDesignAbstraction("PARENT", make_tuple("_", "14", "15"));

    QueryEvaluator queryEvaluator(pkb);
    QueryParser queryParser;

    string declaration = "assign a; while w;";
    string query1 = "Select a such that Parent(14, a)";
    string query2 = "Select w such that Parent(w, 15)";

    queryParser.parse(declaration);

    SelectExpression *exp1 = queryParser.parse(query1);
    SelectExpression *exp2 = queryParser.parse(query2);

    vector<string> res1 = queryEvaluator.evaluate(exp1);
    vector<string> res2 = queryEvaluator.evaluate(exp2);

    REQUIRE(Utilities::checkIfPresent(res1, "15"));
    REQUIRE(Utilities::checkIfPresent(res2, "14"));
}

TEST_CASE("TestCase10_EvaluateSelectStatementWithSuchThatParentSynonyms_ShouldSuccess") {
    PKB pkb;

    pkb.addDesignEntity("ASSIGNMENT", make_tuple("ASSIGNMENT", "17"));
    pkb.addDesignEntity("WHILE", make_tuple("WHILE", "16"));
    pkb.addDesignAbstraction("PARENT", make_tuple("_", "16", "17"));

    QueryEvaluator queryEvaluator(pkb);
    QueryParser queryParser;

    string declaration = "assign a; while w;";
    string query1 = "Select a such that Parent(w, a)";
    string query2 = "Select w such that Parent(w, a)";

    queryParser.parse(declaration);

    SelectExpression *exp1 = queryParser.parse(query1);
    SelectExpression *exp2 = queryParser.parse(query2);

    vector<string> res1 = queryEvaluator.evaluate(exp1);
    vector<string> res2 = queryEvaluator.evaluate(exp2);

    REQUIRE(Utilities::checkIfPresent(res1, "17"));
    REQUIRE(Utilities::checkIfPresent(res2, "16"));
}

TEST_CASE("TestCase11_EvaluateSelectStatementWithSuchThatFollowsStar_ShouldSuccess") {
    PKB pkb;

    pkb.addDesignEntity("ASSIGNMENT", make_tuple("ASSIGNMENT", "18"));
    pkb.addDesignEntity("ASSIGNMENT", make_tuple("ASSIGNMENT", "20"));
    pkb.addDesignAbstraction("FOLLOWSSTAR", make_tuple("_", "18", "20"));

    QueryEvaluator queryEvaluator(pkb);
    QueryParser queryParser;

    string declaration = "assign a;";
    string query1 = "Select a such that Follows*(a, 20)";
    string query2 = "Select a such that Follows*(18, a)";

    queryParser.parse(declaration);

    SelectExpression *exp1 = queryParser.parse(query1);
    SelectExpression *exp2 = queryParser.parse(query2);

    vector<string> res1 = queryEvaluator.evaluate(exp1);
    vector<string> res2 = queryEvaluator.evaluate(exp2);

    REQUIRE(Utilities::checkIfPresent(res1, "18"));
    REQUIRE(Utilities::checkIfPresent(res2, "20"));
}

TEST_CASE("TestCase12_EvaluateSelectStatementWithSuchThatFollowsStarSynonyms_ShouldSuccess") {
    PKB pkb;

    pkb.addDesignEntity("ASSIGNMENT", make_tuple("ASSIGNMENT", "23"));
    pkb.addDesignEntity("WHILE", make_tuple("WHILE", "21"));
    pkb.addDesignAbstraction("FOLLOWSSTAR", make_tuple("_", "21", "23"));

    QueryEvaluator queryEvaluator(pkb);
    QueryParser queryParser;

    string declaration = "assign a; while w;";
    string query1 = "Select a such that Follows*(w, a)";
    string query2 = "Select w such that Follows*(w, a)";

    queryParser.parse(declaration);

    SelectExpression *exp1 = queryParser.parse(query1);
    SelectExpression *exp2 = queryParser.parse(query2);


    vector<string> res1 = queryEvaluator.evaluate(exp1);
    vector<string> res2 = queryEvaluator.evaluate(exp2);

    REQUIRE(Utilities::checkIfPresent(res1, "23"));
    REQUIRE(Utilities::checkIfPresent(res2, "21"));
}

TEST_CASE("TestCase13_EvaluateSelectStatementWithSuchThatParentStar_ShouldSuccess") {
    PKB pkb;

    pkb.addDesignEntity("ASSIGNMENT", make_tuple("ASSIGNMENT", "26"));
    pkb.addDesignEntity("WHILE", make_tuple("WHILE", "24"));
    pkb.addDesignAbstraction("PARENTSTAR", make_tuple("_", "24", "26"));

    QueryEvaluator queryEvaluator(pkb);
    QueryParser queryParser;

    string declaration = "assign a; while w;";
    string query1 = "Select a such that Parent*(24, a)";
    string query2 = "Select w such that Parent*(w, 26)";

    queryParser.parse(declaration);

    SelectExpression *exp1 = queryParser.parse(query1);
    SelectExpression *exp2 = queryParser.parse(query2);

    vector<string> res1 = queryEvaluator.evaluate(exp1);
    vector<string> res2 = queryEvaluator.evaluate(exp2);

    REQUIRE(Utilities::checkIfPresent(res1, "26"));
    REQUIRE(Utilities::checkIfPresent(res2, "24"));
}

TEST_CASE("TestCase14_EvaluateSelectStatementWithSuchThatParentStarSynonyms_ShouldSuccess") {
    PKB pkb;

    pkb.addDesignEntity("ASSIGNMENT", make_tuple("ASSIGNMENT", "29"));
    pkb.addDesignEntity("WHILE", make_tuple("WHILE", "27"));
    pkb.addDesignAbstraction("PARENTSTAR", make_tuple("_", "27", "29"));

    QueryEvaluator queryEvaluator(pkb);
    QueryParser queryParser;

    string declaration = "assign a; while w;";
    string query1 = "Select a such that Parent*(w, a)";
    string query2 = "Select w such that Parent*(w, a)";

    queryParser.parse(declaration);

    SelectExpression *exp1 = queryParser.parse(query1);
    SelectExpression *exp2 = queryParser.parse(query2);

    vector<string> res1 = queryEvaluator.evaluate(exp1);
    vector<string> res2 = queryEvaluator.evaluate(exp2);

    REQUIRE(Utilities::checkIfPresent(res1, "29"));
    REQUIRE(Utilities::checkIfPresent(res2, "27"));
}