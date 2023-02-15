//
// Created by Jai Lulla  on 16/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of Assign Pattern") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addAssignPattern("a", "123++", "2");

        vector<AssignPattern*> result = pkbTest.getAllRightHandExpressions();

        REQUIRE(result.size() != 0);
    }
}

TEST_CASE("Test 2: Obtaining the Correct Result using getAllRightHandExpressionsOfAVariable() API") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addAssignPattern("b", "1+2+3", "3");

        unordered_map<string, string> result = pkbTest.getAllRightHandExpressionsOfAVariable("b");

        REQUIRE(result.find("3")->second == "1+2+3");
    }
}

TEST_CASE("Test 3: Obtaining the Correct Result using getRightHandExpressionOfAVariableOnAParticularLineNumber() API") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addAssignPattern("c", "--123", "4");

        string result = pkbTest.getRightHandExpressionOfAVariableOnAParticularLineNumber("c", "4");

        REQUIRE(result == "--123");
    }
}

TEST_CASE("Test 4: Query for a non-existent variable name using getAllRightHandExpressionsOfAVariable() API") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addAssignPattern("d", "1-2-3", "5");

        unordered_map<string, string> result = pkbTest.getAllRightHandExpressionsOfAVariable("non_existent_variable");

        REQUIRE(result.size() == 0);
    }
}

TEST_CASE("Test 5: Query for a non-existent variable name and a non-existent line number using getRightHandExpressionOfAVariableOnAParticularLineNumber() API") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addAssignPattern("e", "**123", "6");

        string result = pkbTest.getRightHandExpressionOfAVariableOnAParticularLineNumber("non_existent_variable", "-1");

        REQUIRE(result == "");
    }
}

TEST_CASE("Test 6: Query for an existent variable name and a non-existent line number using getRightHandExpressionOfAVariableOnAParticularLineNumber() API") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addAssignPattern("f", "1*2*3", "7");

        string result = pkbTest.getRightHandExpressionOfAVariableOnAParticularLineNumber("f", "-1");

        REQUIRE(result == "");
    }
}

TEST_CASE("Test 7: Query for a non-existent variable name and an existent line number using getRightHandExpressionOfAVariableOnAParticularLineNumber() API") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addAssignPattern("g", "123//", "8");

        string result = pkbTest.getRightHandExpressionOfAVariableOnAParticularLineNumber("non_existent_variable", "8");

        REQUIRE(result == "");
    }
}

TEST_CASE("Test 8: Query for a non-existent line number after using getAllRightHandExpressionsOfAVariable() API") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addAssignPattern("h", "//123", "9");

        unordered_map<string, string> result = pkbTest.getAllRightHandExpressionsOfAVariable("h");

        REQUIRE(result.find("-1") == result.end());
    }
}

TEST_CASE("Test 9: Query for a existent variable name with multiple expressions on different lines using getAllRightHandExpressionsOfAVariable() API") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addAssignPattern("i", "1/2/3/", "10");
        pkbTest.addAssignPattern("i", "/1/2/3", "11");

        unordered_map<string, string> result = pkbTest.getAllRightHandExpressionsOfAVariable("i");

        REQUIRE(result.size() == 2);
    }
}

TEST_CASE("Test 10:  Query for a existent variable name with various patterns existent on various line numbers using getRightHandExpressionOfAVariableOnAParticularLineNumber() API") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addAssignPattern("j", "1%2%3%", "12");
        pkbTest.addAssignPattern("j", "1%2%3", "13");

        string result1 = pkbTest.getRightHandExpressionOfAVariableOnAParticularLineNumber("j", "12");
        string result2 = pkbTest.getRightHandExpressionOfAVariableOnAParticularLineNumber("j", "13");

        REQUIRE(((result1 == "1%2%3%") && (result2 == "1%2%3")));
    }
}
