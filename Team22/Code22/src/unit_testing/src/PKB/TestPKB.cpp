//
// Created by Jai Lulla  on 3/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Trial PKB Test") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("VARIABLE", make_tuple("a", "1"));

//        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("procedure", "v [name]", "1 [line no]"));
//        pkbTest.addDesignEntity("PROCEDURE", make_tuple("a", "2"));

        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "a");

        cout << pkbResult.toString() << endl;

        Result expectedResult("VARIABLE", "a", vector<string> {"1"});

        cout << expectedResult.toString() << endl;

        cout << (pkbResult.areEqual(expectedResult) ? "Yes" : "No") << endl;
//    REQUIRE(pkbTest.addDesignEntity("variable", make_tuple("a", "1")))
//    REQUIRE(1==1);
        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

// Need to section below, as some code is being carried forward unintentionally
TEST_CASE("PKB Test 1: Design Entity : Same Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest1 = PKB();
        pkbTest1.addDesignEntity("VARIABLE", make_tuple("a1", "1"));
        Result pkbResult1 = pkbTest1.getDesignEntity("VARIABLE", "a1");

        Result expectedResult1("VARIABLE", "a1", vector<string>{"1"});

        REQUIRE(pkbResult1.areEqual(expectedResult1));
    }
}

TEST_CASE("PKB Test 2: Design Entity : Same Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest2 = PKB();
        pkbTest2.addDesignEntity("VARIABLE", make_tuple("b2", "1"));
        Result pkbResult2 = pkbTest2.getDesignEntity("VARIABLE", "b2");

        Result unexpectedResult2("VARIABLE", "a2", vector<string>{"1"});

        REQUIRE(!pkbResult2.areEqual(unexpectedResult2));
    }
}

TEST_CASE("PKB Test 3: Design Entity : Same Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest3 = PKB();
        pkbTest3.addDesignEntity("VARIABLE", make_tuple("b3", "2"));
        Result pkbResult3 = pkbTest3.getDesignEntity("VARIABLE", "b3");

        Result unexpectedResult3("VARIABLE", "a3", vector<string>{"1"});

        REQUIRE(!pkbResult3.areEqual(unexpectedResult3));
    }
}

TEST_CASE("PKB Test 4: Design Entity : Different Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest4 = PKB();
        pkbTest4.addDesignEntity("PROCEDURE", make_tuple("a4", "1"));
        Result pkbResult4 = pkbTest4.getDesignEntity("PROCEDURE", "a4");

        Result unexpectedResult4("VARIABLE", "a4", vector<string>{"1"});

        REQUIRE(!pkbResult4.areEqual(unexpectedResult4));
    }
}

TEST_CASE("PKB Test 5: Design Entity : Different Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest5 = PKB();
        pkbTest5.addDesignEntity("PROCEDURE", make_tuple("a5", "1"));
        Result pkbResult5 = pkbTest5.getDesignEntity("PROCEDURE", "a5");

        Result unexpectedResult5("VARIABLE", "b5", vector<string>{"1"});

        REQUIRE(!pkbResult5.areEqual(unexpectedResult5));
    }
}

TEST_CASE("PKB Test 6: Design Entity : Different Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest6 = PKB();
        pkbTest6.addDesignEntity("PROCEDURE", make_tuple("a6", "1"));
        Result pkbResult6 = pkbTest6.getDesignEntity("PROCEDURE", "a6");

        Result unexpectedResult6("VARIABLE", "b6", vector<string>{"2"});

        REQUIRE(!pkbResult6.areEqual(unexpectedResult6));
    }
}

TEST_CASE("PKB Test 7: Design Entity : Same Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest7 = PKB();
        pkbTest7.addDesignEntity("VARIABLE", make_tuple("a7", "2"));
        Result pkbResult7 = pkbTest7.getDesignEntity("VARIABLE", "a7");

        Result unexpectedResult7("VARIABLE", "a7", vector<string>{"1"});

        REQUIRE(!pkbResult7.areEqual(unexpectedResult7));
    }
}

TEST_CASE("PKB Test 8: Design Entity : Different Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest8 = PKB();
        pkbTest8.addDesignEntity("VARIABLE", make_tuple("a8", "2"));
        Result pkbResult8 = pkbTest8.getDesignEntity("VARIABLE", "a8");

        Result unexpectedResult8("PROCEDURE", "a8", vector<string>{"1"});

        REQUIRE(!pkbResult8.areEqual(unexpectedResult8));
    }
}

TEST_CASE("PKB Test 9: DesignAbstraction : Modifies-Assignment : Same Type, Same Type Being Abstracted, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest9 = PKB();
        pkbTest9.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "v", "1"));
        Result pkbResult9 = pkbTest9.getDesignAbstraction("MODIFIES", make_pair("ASSIGNMENT", "v"));

        cout << pkbResult9.toString() << endl;

        Result expectedResult9("MODIFIES:ASSIGNMENT", "v", vector<string>{"1"});

        cout << expectedResult9.toString() << endl;

        REQUIRE(pkbResult9.areEqual(expectedResult9));
    }
}

TEST_CASE("PKB Test 10: DesignAbstraction : Modifies-Read : Same Type, Same Type Being Abstracted, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest10 = PKB();
        pkbTest10.addDesignAbstraction("MODIFIES", make_tuple("READ", "v", "1"));
        Result pkbResult10 = pkbTest10.getDesignAbstraction("MODIFIES", make_pair("READ", "v"));

        Result expectedResult10("MODIFIES:READ", "v", vector<string>{"1"});

        REQUIRE(pkbResult10.areEqual(expectedResult10));
    }
}

TEST_CASE("PKB Test 11: DesignAbstraction : Modifies-Statement : Same Type, Same Type Being Abstracted, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest11 = PKB();
        pkbTest11.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "v", "1"));
        Result pkbResult11 = pkbTest11.getDesignAbstraction("MODIFIES", make_pair("STATEMENT", "v"));

        Result expectedResult11("MODIFIES:STATEMENT", "v", vector<string>{"1"});

        REQUIRE(pkbResult11.areEqual(expectedResult11));
    }
}
