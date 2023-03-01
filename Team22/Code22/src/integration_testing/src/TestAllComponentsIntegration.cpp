#include "catch.hpp"

#include "SP/SPDriver.h"
#include "QPS/Parser.h"
#include "QPS/Evaluator.h"
#include "QPS/Exceptions.h"
#include <iostream>
#include <cstdint>
#include <filesystem>

using namespace std;

void require(bool b) {
    REQUIRE(b);
}

TEST_CASE("TestCase1_StandardExampleSIMPLESource_ShouldSuccess") {
    SPDriver driver;
    std::string inputFilePath;

    inputFilePath = "Sample_source2.txt";

    string code = "procedure Example {\n"
                  "  x = 2;\n"
                  "  z = 3;\n"
                  "  i = 5;\n"
                  "  while (i!=0) {\n"
                  "    x = x - 1;\n"
                  "    if (x==1) then {\n"
                  "      z = x + 1; }\n"
                  "    else {\n"
                  "      y = z + x; }\n"
                  "    z = z + x + i;\n"
                  "    read q;\n"
                  "    i = i - 1; }\n"
                  "    print p; }";
    ofstream temp_file;
    temp_file.open(inputFilePath);
    temp_file << code;
    temp_file.close();

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

    QueryEvaluator evaluator(standardExampleSIMPLESourceChecker);

    string declaration1 = "variable v;";
    string query1 = "Select v";
    QueryParser parser;
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
    parser = QueryParser();
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
    parser = QueryParser();
    parser.parse(declaration3);
    auto exp3 = parser.parse(query3);
    vector<string> res_3 = evaluator.evaluate(exp3);
    string output3;
    for (const string& r : res_3) {
        output3 += r + " ";
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
    string declaration4 = "stmt a;";
    string query4 = "Select a such that Follows*(3, a)";
    parser = QueryParser();
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
    string declaration5 = "stmt a;";
    string query5 = "Select a such that Follows(3, a)";
    parser = QueryParser();
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
    parser = QueryParser();
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
    parser = QueryParser();
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
    parser = QueryParser();
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

    // Testing Assign Patten
    string declaration9 = "assign a;";
    string query9 = "Select a pattern a(\"x\", \"x - 1\")";
    parser = QueryParser();
    parser.parse(declaration9);
    auto exp9 = parser.parse(query9);
    vector<string> res_9 = evaluator.evaluate(exp9);
    string output9;
    for (const string& r : res_9) {
        output9 += r;
    }

    REQUIRE(output9.find('5') != std::string::npos);
    REQUIRE(output9.find('6') == std::string::npos);

    REQUIRE(filesystem::remove(inputFilePath));
}

TEST_CASE("TestCase2_GrandSIMPLESource_ShouldSuccess") {
    PKB standardExampleSIMPLESourceChecker = PKB();
    standardExampleSIMPLESourceChecker.clearAllDatabases();
    SPDriver driver;
    std::string inputFilePath;

    inputFilePath = "Sample_source3.txt";

    string code = "procedure Example {\n"
                  " x = 2;\n"
                  " while (i!=0) {\n"
                  "   if (x > 1) then {\n"
                  "     z = x + 1; }\n"
                  "   else {\n"
                  "     y = z + x;\n"
                  "     if (x >= 5) then {\n"
                  "        z = x + 1;\n"
                  "        while ( x < 10) {\n"
                  "           x = x - 1;\n"
                  "           while ((x <= 9) || ((z % 2) == 1)) {\n"
                  "             anx = 1;\n"
                  "             if (z == 1) then {\n"
                  "               z = 2;\n"
                  "             } else {\n"
                  "               z = 3;\n"
                  "               while (!(!(j < 0))) {\n"
                  "                 j = ((1 + 2) * (3 + 4) + 5) % 6 / 7 ;\n"
                  "               }\n"
                  "             }\n"
                  "           }\n"
                  "        }\n"
                  "     }\n"
                  "     else {\n"
                  "       print x;\n"
                  "     }\n"
                  "   }\n"
                  " }\n"
                  "}";
    ofstream temp_file;
    temp_file.open(inputFilePath);
    temp_file << code;
    temp_file.close();

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
    parser = QueryParser();
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

    // Testing Parent
    string declaration3 = "stmt s;";
    string query3 = "Select s such that Parent(8, s)";
    parser = QueryParser();
    parser.parse(declaration3);
    auto exp3 = parser.parse(query3);
    vector<string> res_3 = evaluator.evaluate(exp3);
    string output3;
    for (const string& r : res_3) {
        output3 += r;
    }

    REQUIRE(output3.find('8') == std::string::npos);
    REQUIRE(output3.find('9') != std::string::npos);
    REQUIRE(output3.find("10") != std::string::npos);
    REQUIRE(output3.find("11") == std::string::npos);

    // Testing Parent*
    string declaration4 = "stmt s;";
    string query4 = "Select s such that Parent*(8, s)";
    parser = QueryParser();
    parser.parse(declaration4);
    auto exp4 = parser.parse(query4);
    vector<string> res_4 = evaluator.evaluate(exp4);
    string output4;
    for (const string& r : res_4) {
        output4 += r;
    }

    REQUIRE(output4.find('8') == std::string::npos);
    REQUIRE(output4.find('9') != std::string::npos);
    REQUIRE(output4.find("10") != std::string::npos);
    REQUIRE(output4.find("11") != std::string::npos);
    REQUIRE(output4.find("12") != std::string::npos);
    REQUIRE(output4.find("13") != std::string::npos);
    REQUIRE(output4.find("14") != std::string::npos);
    REQUIRE(output4.find("15") != std::string::npos);
    REQUIRE(output4.find("16") != std::string::npos);

    // Testing Uses
    string declaration5 = "variable v;";
    string query5 = "Select v such that Uses(15, v)";
    parser = QueryParser();
    parser.parse(declaration5);
    auto exp5 = parser.parse(query5);
    vector<string> res_5 = evaluator.evaluate(exp5);
    string output5;
    for (const string& r : res_5) {
        output5 += r;
    }

    REQUIRE(output5.find("anx") == std::string::npos);
    REQUIRE(output5.find('j') != std::string::npos);

    // Testing Modifies
    string declaration6 = "variable v;";
    string query6 = "Select v such that Modifies(16, v)";
    parser = QueryParser();
    parser.parse(declaration6);
    auto exp6 = parser.parse(query6);
    vector<string> res_6 = evaluator.evaluate(exp6);
    string output6;
    for (const string& r : res_6) {
        output6 += r;
    }

    REQUIRE(output6.find("anx") == std::string::npos);
    REQUIRE(output6.find('j') != std::string::npos);

    // Testing Follows
    string declaration7 = "stmt s;";
    string query7 = "Select s such that Follows(14, s)";
    parser = QueryParser();
    parser.parse(declaration7);
    auto exp7 = parser.parse(query7);
    vector<string> res_7 = evaluator.evaluate(exp7);
    string output7;
    for (const string& r : res_7) {
        output7 += r;
    }

    REQUIRE(output7.find("16") == std::string::npos);
    REQUIRE(output7.find("15") != std::string::npos);

    // Testing Follows*
    string declaration8 = "stmt s;";
    string query8 = "Select s such that Follows*(14, s)";
    parser = QueryParser();
    parser.parse(declaration8);
    auto exp8 = parser.parse(query8);
    vector<string> res_8 = evaluator.evaluate(exp8);
    string output8;
    for (const string& r : res_8) {
        output8 += r;
    }

    REQUIRE(output8.find("16") == std::string::npos);
    REQUIRE(output8.find("15") != std::string::npos);

    // Testing Assign Patten
    string declaration9 = "assign a;";
    string query9 = "Select a pattern a(\"j\", _)";
    parser = QueryParser();
    parser.parse(declaration9);
    auto exp9 = parser.parse(query9);
    vector<string> res_9 = evaluator.evaluate(exp9);
    string output9;
    for (const string& r : res_9) {
        output9 += r;
    }
    REQUIRE(output9.find("16") != std::string::npos);
    REQUIRE(output9.find("15") == std::string::npos);

    REQUIRE(filesystem::remove(inputFilePath));

    // Testing Uses with ident
    string declaration10 = "assign a;";
    string query10 = "Select a such that Uses(a, \"x\")";
    parser = QueryParser();
    parser.parse(declaration10);
    auto exp10 = parser.parse(query10);
    vector<string> res_10 = evaluator.evaluate(exp10);
    string output10;
    for (const string &r: res_10) {
        output10 += r;
    }

    REQUIRE(output10.find('4') != std::string::npos);
    REQUIRE(output10.find('5') != std::string::npos);
    REQUIRE(output10.find('7') != std::string::npos);
    REQUIRE(output10.find('9') != std::string::npos);
    REQUIRE(output10.find('1') == std::string::npos);
}
