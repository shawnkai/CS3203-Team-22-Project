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

    string declaration3 = "stmt s;";
    string query3 = "Select s such that Parent(4, s)";
    parser.parse(declaration3);
    auto exp3 = parser.parse(query3);
    vector<string> res_3 = evaluator.evaluate(exp3);
    string output3;
    for (const string& r : res_3) {
        output3 += r;
    }
    cout << "Output 3" << output3 << endl; ;

    REQUIRE(output3.find('5') != std::string::npos);
    REQUIRE(output3.find('6') != std::string::npos);
    REQUIRE(output3.find('7') == std::string::npos);
    REQUIRE(output3.find('8') == std::string::npos);
    REQUIRE(output3.find('9') != std::string::npos);
    REQUIRE(output3.find("10") != std::string::npos);
    REQUIRE(output3.find("11") != std::string::npos);
    REQUIRE(output3.find("12") == std::string::npos);
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
