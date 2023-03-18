//
// Created by Jai Lulla  on 8/3/23.
//

#include <iostream>

#include "catch.hpp"

#include "PKB/DesignAbstractions/DesignAbstractionsFactory.h"
#include "PKB/Exceptions/InvalidAbstractionTypeException.cpp"

using namespace std;

TEST_CASE("Test 1: Catch InvalidAbstractionTypeException") {
    bool exceptionThrown = false;
    try {
        DesignAbstractionsFactory::createDesignAbstraction("INVALID_ABSTRACTION_TYPE", make_tuple("INVALID", "INVALID", "INVALID"));
    } catch (exception &e) {
        exceptionThrown = true;
    }
    REQUIRE(exceptionThrown);
}
