//
// Created by Jai Lulla  on 8/3/23.
//

#include <iostream>

#include "catch.hpp"

#include "PKB/DesignEntities/DesignEntitiesFactory.h"
#include "PKB/Exceptions/InvalidEntityTypeException.cpp"

using namespace std;

TEST_CASE("Test 1: Catch InvalidEntityTypeException") {
    bool exceptionThrown = false;

    try {
        DesignEntitiesFactory::createDesignEntity("INVALID_ENTITY_TYPE", make_pair("INVALID", "INVALID"));
    } catch (InvalidEntityTypeException &e) {
        exceptionThrown = true;
    }

    REQUIRE(exceptionThrown);
}
