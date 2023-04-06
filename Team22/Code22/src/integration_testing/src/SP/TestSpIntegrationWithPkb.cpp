//
// Created by Yi Zhang on 17/3/23.
//

#include "catch.hpp"

#include "SP/SPDriver.h"
#include "PKB/PKB.h"

TEST_CASE("TestCase1_TestSPPKBIntegration_ShouldSuccess") {
    PKB standardExampleSIMPLESourceChecker = PKB();
    standardExampleSIMPLESourceChecker.clearAllDatabases();
    SPDriver driver;
    std::string inputFilePath;

    inputFilePath = "Sample_source.txt";

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

    vector<int> resultOne = standardExampleSIMPLESourceChecker.getTopologicallySortedElementsDatabase("Example");
    REQUIRE(resultOne.size() == 17);
}
