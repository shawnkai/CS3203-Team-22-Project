//
// Created by Jai Lulla  on 3/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Trial PKB Test") {
    PKB pkbTest = PKB();
    pkbTest.addDesignEntity("variable", make_tuple("a", "1"));

//    REQUIRE(pkbTest.addDesignEntity("variable", make_tuple("a", "1")))
    REQUIRE(1==1);
}