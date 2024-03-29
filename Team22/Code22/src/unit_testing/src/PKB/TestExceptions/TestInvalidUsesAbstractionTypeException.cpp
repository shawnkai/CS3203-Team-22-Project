//
// Created by Jai Lulla  on 9/3/23.
//

#include <iostream>

#include "catch.hpp"

#include "PKB/DesignAbstractions/UsesAbstraction/UsesFactory.h"

#include "PKB/Exceptions/InvalidUsesAbstractionTypeException.cpp"

using namespace std;

TEST_CASE("Test 1: Catch InvalidUsesAbstractionTypeException In UsesFactory") {
    bool exceptionThrown = false;

    try {
        UsesFactory::createUsesAbstraction(make_tuple("INVALID", "INVALID", "INVALID"));
    } catch (InvalidUsesAbstractionTypeException &e) {
        exceptionThrown = true;
    }

    REQUIRE(exceptionThrown);
}
