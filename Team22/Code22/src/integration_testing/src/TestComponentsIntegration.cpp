#include "SP/SPDriver.h"

#include "catch.hpp"
using namespace std;
void require(bool b) {
    REQUIRE(b);
}

TEST_CASE("TestCase1_StandardExampleSIMPLESource_ShouldSuccess") {
    SPDriver driver;
    std::string inputFilePath;
#if __APPLE__
    inputFilePath = "../../../tests/Sample_source2.txt";
#endif
    driver.parseSimpleProgram(inputFilePath);

    PKB standardExampleSIMPLESourceChecker = PKB();
    Result pkbResult = standardExampleSIMPLESourceChecker.getDesignEntity("ASSIGNMENT", "x");
    cout << pkbResult.toString() << endl;
    Result expectedResult("ASSIGNMENT", "x", vector<string> {"1", "5", "7", "8", "9"});
    REQUIRE(pkbResult.areEqual(expectedResult));

    //Result pkbResult2 = standardExampleSIMPLESourceChecker.getDesignEntity("CONSTANT", "z");
}

