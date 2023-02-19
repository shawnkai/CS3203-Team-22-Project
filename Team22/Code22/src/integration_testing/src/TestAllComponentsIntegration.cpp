#include "catch.hpp"

#include "SP/SPDriver.h"
#include "QPS/Parser.h"
#include "QPS/Evaluator.h"

using namespace std;

void require(bool b) {
    REQUIRE(b);
}

TEST_CASE("TestCase1_StandardExampleSIMPLESource_ShouldSuccess") {
    SPDriver driver;
    std::string inputFilePath;
#if __APPLE__
//    inputFilePath = "../../../tests/Sample_source2.txt";
    inputFilePath = "Sample_source2.txt";
#endif
    driver.parseSimpleProgram(inputFilePath);

    PKB standardExampleSIMPLESourceChecker = PKB();
    Result pkbResult = standardExampleSIMPLESourceChecker.getDesignAbstraction("MODIFIES",
                                                                               make_tuple("ASSIGNMENT", "x"));
    Result expectedResult("MODIFIES:ASSIGNMENT", "x", vector<string> {"1", "5"});

    REQUIRE(pkbResult.areEqual(expectedResult));
    Result pkbResult2 = standardExampleSIMPLESourceChecker.getDesignAbstraction("USES",
                                                                                     make_tuple("ASSIGNMENT", "i"));
    Result expectedResult2("USES:ASSIGNMENT", "i", vector<string>{"9", "11"});
    REQUIRE(pkbResult2.areEqual(expectedResult2));

    QueryParser parser;
    QueryEvaluator evaluator(standardExampleSIMPLESourceChecker);

    string declaration1 = "variable v;";
    string query1 = "Select v";
    parser.parse(declaration1);
    auto exp1 = parser.parse(query1);
    vector<string> exp_res = evaluator.evaluate(exp1);
    string output1;
    for (const string& r : exp_res) {
        output1 += r;
    }
    REQUIRE(output1.find('p') != std::string::npos);
    REQUIRE(output1.find('z') != std::string::npos);
    REQUIRE(output1.find('y') != std::string::npos);
    REQUIRE(output1.find('x') != std::string::npos);
    REQUIRE(output1.find('i') != std::string::npos);
    REQUIRE(output1.find('q') != std::string::npos);

    string declaration2 = "stmt m; if if;";
    string query2 = "Select m such that Parent(if, m)";
    parser.parse(declaration2);
    auto exp2 = parser.parse(query2);
    vector<string> res_2 = evaluator.evaluate(exp2);
    string output2;
    for (const string& r : res_2) {
        output2 += r;
    }

    REQUIRE(output2.find('7') != std::string::npos);
    REQUIRE(output2.find('8') != std::string::npos);

    // Testing Parent
    string declaration3 = "stmt s;";
    string query3 = "Select s such that Parent(4, s)";
    parser.parse(declaration3);
    auto exp3 = parser.parse(query3);
    vector<string> res_3 = evaluator.evaluate(exp3);
    string output3;
    for (const string& r : res_3) {
        output3 += r;
    }

    REQUIRE(output3.find('5') != std::string::npos);
    REQUIRE(output3.find('6') != std::string::npos);
    REQUIRE(output3.find('7') == std::string::npos);
    REQUIRE(output3.find('8') == std::string::npos);
    REQUIRE(output3.find('9') != std::string::npos);
    REQUIRE(output3.find("10") != std::string::npos);
    REQUIRE(output3.find("11") != std::string::npos);
    REQUIRE(output3.find("12") == std::string::npos);

    // Testing Follows*
    string declaration4 = "variable a;";
    string query4 = "Select a such that Follows*(3, a)";
    parser.parse(declaration4);
    auto exp4 = parser.parse(query4);
    vector<string> res_4 = evaluator.evaluate(exp4);
    string output4;
    for (const string& r : res_4) {
        output4 += r;
    }

    REQUIRE(output4.find('4') != std::string::npos);
    REQUIRE(output4.find("12") != std::string::npos);

    // Testing Follows
    string declaration5 = "variable a;";
    string query5 = "Select a such that Follows(3, a)";
    parser.parse(declaration5);
    auto exp5 = parser.parse(query5);
    vector<string> res_5 = evaluator.evaluate(exp5);
    string output5;
    for (const string& r : res_5) {
        output5 += r;
    }

    REQUIRE(output5.find('4') != std::string::npos);
    REQUIRE(output5.find("12") == std::string::npos);

    // Testing Uses
    string declaration6 = "variable v;";
    string query6 = "Select v such that Uses(9, v)";
    parser.parse(declaration6);
    auto exp6 = parser.parse(query6);
    vector<string> res_6 = evaluator.evaluate(exp6);
    string output6;
    for (const string& r : res_6) {
        output6 += r;
    }

    REQUIRE(output6.find('i') != std::string::npos);
    REQUIRE(output6.find('z') != std::string::npos);
    REQUIRE(output6.find('x') != std::string::npos);
    REQUIRE(output6.find('o') == std::string::npos);

    // Testing Modifies
    string declaration7 = "variable v;";
    string query7 = "Select v such that Modifies(7, v)";
    parser.parse(declaration7);
    auto exp7 = parser.parse(query7);
    vector<string> res_7 = evaluator.evaluate(exp7);
    string output7;
    for (const string& r : res_7) {
        output7 += r;
    }

    REQUIRE(output7.find('i') == std::string::npos);
    REQUIRE(output7.find('z') != std::string::npos);
    REQUIRE(output7.find('x') == std::string::npos);

    // Testing Parent*
    string declaration8 = "assign a; while w;";
    string query8 = "Select a such that Parent* (w, a)";
    parser.parse(declaration8);
    auto exp8 = parser.parse(query8);
    vector<string> res_8 = evaluator.evaluate(exp8);
    string output8;
    for (const string& r : res_8) {
        output8 += r;
    }

    REQUIRE(output8.find('5') != std::string::npos);
    REQUIRE(output8.find('6') == std::string::npos);
    REQUIRE(output8.find('7') != std::string::npos);
    REQUIRE(output8.find('8') != std::string::npos);
    REQUIRE(output8.find('9') != std::string::npos);
    REQUIRE(output8.find("10") == std::string::npos);
    REQUIRE(output8.find("11") != std::string::npos);
    REQUIRE(output8.find("12") == std::string::npos);
}

TEST_CASE("TestCase2_GrandSIMPLESource_ShouldSuccess") {
    PKB standardExampleSIMPLESourceChecker = PKB();
    standardExampleSIMPLESourceChecker.clearAllDatabases();
    SPDriver driver;
    std::string inputFilePath;
#if __APPLE__
    inputFilePath = "Sample_source3.txt";
#endif
    driver.parseSimpleProgram(inputFilePath);

    //PKB standardExampleSIMPLESourceChecker = PKB();
    Result pkbResult = standardExampleSIMPLESourceChecker.getDesignAbstraction("MODIFIES",
                                                                               make_tuple("ASSIGNMENT", "x"));
    Result expectedResult("MODIFIES:ASSIGNMENT", "x", vector<string> {"1", "9"});
    REQUIRE(pkbResult.areEqual(expectedResult));

    Result pkbResult2 = standardExampleSIMPLESourceChecker.getDesignAbstraction("USES",
                                                                                make_tuple("ASSIGNMENT", "x"));
    Result expectedResult2("USES:ASSIGNMENT", "x", vector<string>{ "4", "5", "7", "9"});
    REQUIRE(pkbResult2.areEqual(expectedResult2));

    QueryParser parser;
    QueryEvaluator evaluator(standardExampleSIMPLESourceChecker);

    string declaration1 = "variable v;";
    string query1 = "Select v";
    parser.parse(declaration1);
    auto exp1 = parser.parse(query1);
    vector<string> exp_res = evaluator.evaluate(exp1);
    string output1;
    for (const string& r : exp_res) {
        output1 += r;
    }
    REQUIRE(output1.find("anx") != std::string::npos);
    REQUIRE(output1.find('z') != std::string::npos);
    REQUIRE(output1.find('y') != std::string::npos);
    REQUIRE(output1.find('x') != std::string::npos);
    REQUIRE(output1.find('i') != std::string::npos);
    REQUIRE(output1.find('j') != std::string::npos);

    string declaration2 = "stmt m; if if;";
    string query2 = "Select m such that Parent*(if, m)";
    parser.parse(declaration2);
    auto exp2 = parser.parse(query2);
    vector<string> res_2 = evaluator.evaluate(exp2);
    string output2;
    for (const string& r : res_2) {
        output2 += r;
    }
    REQUIRE(output2.find('4') != std::string::npos);
    REQUIRE(output2.find('5') != std::string::npos);
    REQUIRE(output2.find('6') != std::string::npos);
    REQUIRE(output2.find('7') != std::string::npos);
    REQUIRE(output2.find('8') != std::string::npos);
    REQUIRE(output2.find('9') != std::string::npos);
    REQUIRE(output2.find("10") != std::string::npos);
    REQUIRE(output2.find("11") != std::string::npos);
    REQUIRE(output2.find("12") != std::string::npos);
    REQUIRE(output2.find("13") != std::string::npos);
    REQUIRE(output2.find("14") != std::string::npos);
    REQUIRE(output2.find("15") != std::string::npos);
    REQUIRE(output2.find("16") != std::string::npos);
    REQUIRE(output2.find("17") != std::string::npos);
}