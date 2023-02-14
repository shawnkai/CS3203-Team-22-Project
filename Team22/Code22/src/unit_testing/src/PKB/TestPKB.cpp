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

TEST_CASE("PKB Test 12: DesignAbstraction : Modifies-Procedure : Same Type, Same Type Being Abstracted, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest12 = PKB();
        pkbTest12.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "v", "1"));
        Result pkbResult12 = pkbTest12.getDesignAbstraction("MODIFIES", make_pair("PROCEDURE", "v"));

        Result expectedResult12("MODIFIES:PROCEDURE", "v", vector<string>{"1"});

        REQUIRE(pkbResult12.areEqual(expectedResult12));
    }
}

TEST_CASE("PKB Test 13: DesignAbstraction : Modifies-ProcedureCall : Same Type, Same Type Being Abstracted, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest13 = PKB();
        pkbTest13.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "v", "1"));
        Result pkbResult13 = pkbTest13.getDesignAbstraction("MODIFIES", make_pair("PROCEDURECALL", "v"));

        Result expectedResult13("MODIFIES:PROCEDURECALL", "v", vector<string>{"1"});

        REQUIRE(pkbResult13.areEqual(expectedResult13));
    }
}

//TEST_CASE("PKB Test 14: DesignAbstraction : Modifies : Same Type, Same Type Being Abstracted, Same Entity Name, Same Occurrence") {
//    SECTION("") {
//        PKB pkbTest14 = PKB();
//        pkbTest14.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "v", "1"));
//        Result pkbResult14 = pkbTest14.getDesignAbstraction("MODIFIES", make_pair("PROCEDURECALL", "v"));
//
//        cout << pkbResult14.toString() << endl;
//
//        Result expectedResult14("MODIFIES:PROCEDURECALL", "v", vector<string>{"1"});
//
//        cout << expectedResult14.toString() << endl;
//
//        REQUIRE(pkbResult14.areEqual(expectedResult14));
//    }
//}

TEST_CASE("PKB Test 15: Design Entity : Statement : Same Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest15 = PKB();
        pkbTest15.addDesignEntity("STATEMENT", make_tuple("a15", "1"));
        Result pkbResult15 = pkbTest15.getDesignEntity("STATEMENT", "a15");

        Result expectedResult15("STATEMENT", "a15", vector<string>{"1"});

        REQUIRE(pkbResult15.areEqual(expectedResult15));
    }
}

TEST_CASE("PKB Test 16: Design Entity : Read Statement : Same Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest16 = PKB();
        pkbTest16.addDesignEntity("READ", make_tuple("a16", "1"));
        Result pkbResult16 = pkbTest16.getDesignEntity("READ", "a16");

        Result expectedResult16("READ", "a16", vector<string>{"1"});

        REQUIRE(pkbResult16.areEqual(expectedResult16));
    }
}

TEST_CASE("PKB Test 17: Design Entity : Variable : Same Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest17 = PKB();
        pkbTest17.addDesignEntity("VARIABLE", make_tuple("a17", "1"));
        Result pkbResult17 = pkbTest17.getDesignEntity("VARIABLE", "a17");

        Result expectedResult17("VARIABLE", "a17", vector<string>{"1"});

        REQUIRE(pkbResult17.areEqual(expectedResult17));
    }
}

TEST_CASE("PKB Test 18: Design Entity : Procedure : Same Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest18 = PKB();
        pkbTest18.addDesignEntity("PROCEDURE", make_tuple("a18", "1"));
        Result pkbResult18 = pkbTest18.getDesignEntity("PROCEDURE", "a18");

        Result expectedResult18("PROCEDURE", "a18", vector<string>{"1"});

        REQUIRE(pkbResult18.areEqual(expectedResult18));
    }
}

//TEST_CASE("PKB Test 19: Design Entity : All Variables : Same Type, Same Entity Name, Same Occurrence") {
//    SECTION("") {
//        PKB pkbTest19 = PKB();
//        pkbTest19.addDesignEntity("VARIABLE", make_tuple("a19", "1"));
//        pkbTest19.addDesignEntity("VARIABLE", make_tuple("a19_a", "1"));
//        pkbTest19.addDesignEntity("VARIABLE", make_tuple("a19_b", "1"));
//        pkbTest19.addDesignEntity("VARIABLE", make_tuple("a19_c", "1"));
//
//        // To verify, right items are being fetched
////        pkbTest19.addDesignEntity("PROCEDURE", make_tuple("a19_d", "1"));
//
//        vector<Result> pkbResult19 = pkbTest19.getAllDesignEntity("VARIABLE");
//
//        Result expectedResult19("VARIABLE", "a19", vector<string>{"1"});
//        Result expectedResult19_a("VARIABLE", "a19_a", vector<string>{"1"});
//        Result expectedResult19_b("VARIABLE", "a19_b", vector<string>{"1"});
//        Result expectedResult19_c("VARIABLE", "a19_c", vector<string>{"1"});
//
//        // Something to do with order while testing hmm.
//        vector<Result> expectedVectorResult19;
//        expectedVectorResult19.push_back(expectedResult19_c);
//        expectedVectorResult19.push_back(expectedResult19_b);
//        expectedVectorResult19.push_back(expectedResult19_a);
//        expectedVectorResult19.push_back(expectedResult19);
//
//        bool hasPassed = true;
//
//        for (int i = 0; i < pkbResult19.size(); i++) {
//
//            cout << pkbResult19[i].toString() << endl;
//            cout << expectedVectorResult19[i].toString() << endl;
//
//            if (pkbResult19[i].areEqual(expectedVectorResult19[i])) {
//                continue;
//            }
//            hasPassed = false;
//            break;
//        }
//
//        REQUIRE(true);
//    }
//}

TEST_CASE("PKB Test 20: Design Entity: Constant : Same Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest20 = PKB();
        pkbTest20.addDesignEntity("CONSTANT", make_tuple("a20", "1"));

        // Adding extra to ensure right database is populated
        pkbTest20.addDesignEntity("VARIABLE", make_tuple("a20", "2"));

        Result pkbResult20 = pkbTest20.getDesignEntity("CONSTANT", "a20");

        Result expectedResult20("CONSTANT", "a20", vector<string>{"1"});

        REQUIRE(pkbResult20.areEqual(expectedResult20));
    }
}

TEST_CASE("PKB Test 21: Design Entity: Print Statement : Same Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest21 = PKB();
        pkbTest21.addDesignEntity("PRINT", make_tuple("a21", "1"));

        // Adding extra to ensure right database is populated
        pkbTest21.addDesignEntity("VARIABLE", make_tuple("a21", "1"));

        Result pkbResult21 = pkbTest21.getDesignEntity("PRINT", "a21");

        Result expectedResult21("PRINT", "a21", vector<string>{"1"});

        REQUIRE(pkbResult21.areEqual(expectedResult21));
    }
}

TEST_CASE("PKB Test 22: DesignAbstraction : Uses-Assignment : Same Type, Same Type Being Abstracted, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest22 = PKB();
        pkbTest22.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "v22", "1"));
        pkbTest22.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "v22", "1"));

        Result pkbResult22 = pkbTest22.getDesignAbstraction("USES", make_pair("ASSIGNMENT", "v22"));

        Result expectedResult22("USES:ASSIGNMENT", "v22", vector<string>{"1"});

        REQUIRE(pkbResult22.areEqual(expectedResult22));
    }
}

TEST_CASE("PKB Test 23: DesignAbstraction : Uses-Print : Same Type, Same Type Being Abstracted, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest23 = PKB();
        pkbTest23.addDesignAbstraction("USES", make_tuple("PRINT", "v", "1"));
        pkbTest23.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "v", "1"));

        Result pkbResult23 = pkbTest23.getDesignAbstraction("USES", make_pair("PRINT", "v"));

        Result expectedResult23("USES:PRINT", "v", vector<string>{"1"});

        REQUIRE(pkbResult23.areEqual(expectedResult23));
    }
}

TEST_CASE("PKB Test 24: DesignAbstraction : Uses-Procedure : Same Type, Same Type Being Abstracted, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest24 = PKB();
        pkbTest24.addDesignAbstraction("USES", make_tuple("PROCEDURE", "v", "1"));
        pkbTest24.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "v", "1"));

        Result pkbResult24 = pkbTest24.getDesignAbstraction("USES", make_pair("PROCEDURE", "v"));

        Result expectedResult24("USES:PROCEDURE", "v", vector<string>{"1"});

        REQUIRE(pkbResult24.areEqual(expectedResult24));
    }
}

TEST_CASE("PKB Test 25: DesignAbstraction : Uses-Statement : Same Type, Same Type Being Abstracted, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest25 = PKB();
        pkbTest25.addDesignAbstraction("USES", make_tuple("STATEMENT", "v", "1"));
        pkbTest25.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "v", "1"));

        Result pkbResult25 = pkbTest25.getDesignAbstraction("USES", make_pair("STATEMENT", "v"));

        Result expectedResult25("USES:STATEMENT", "v", vector<string>{"1"});

        REQUIRE(pkbResult25.areEqual(expectedResult25));
    }
}

TEST_CASE("PKB Test 26: DesignAbstraction : Uses-ProcedureCall : Same Type, Same Type Being Abstracted, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest26 = PKB();
        pkbTest26.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "v", "1"));
        pkbTest26.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "v", "1"));

        Result pkbResult26 = pkbTest26.getDesignAbstraction("USES", make_pair("PROCEDURECALL", "v"));

        Result expectedResult26("USES:PROCEDURECALL", "v", vector<string>{"1"});

        REQUIRE(pkbResult26.areEqual(expectedResult26));
    }
}
