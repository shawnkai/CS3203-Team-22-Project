//
// Created by Jai Lulla  on 9/3/23.
//

#include <iostream>

#include "catch.hpp"

#include "PKB/DesignAbstractions/ModifiesAbstraction/ModifiesFactory.h"

#include "PKB/Exceptions/InvalidModifiesAbstractionTypeException.cpp"

using namespace std;

TEST_CASE("Test 1: Catch InvalidModifiesAbstractionTypeException In ModifiesFactory") {
    bool exceptionThrown = false;
    try {
        ModifiesFactory::createModifiesAbstraction(make_tuple("INVALID", "INVALID", "INVALID"));
    } catch (exception &e) {
        exceptionThrown = true;
    }
    REQUIRE(exceptionThrown);
}
