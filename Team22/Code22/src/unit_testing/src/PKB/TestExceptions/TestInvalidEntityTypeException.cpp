//
// Created by Jai Lulla  on 8/3/23.
//

#include <iostream>

#include "catch.hpp"

#include "PKB/DesignEntities/DesignEntitiesFactory.h"
#include "PKB/Exceptions/InvalidEntityTypeException.cpp"

using namespace std;

TEST_CASE("Test 1: Catch InvalidEntityTypeException", "[!throws][!shouldfail]") {
    DesignEntitiesFactory::createDesignEntity("INVALID_ENTITY_TYPE", make_pair("INVALID", "INVALID"));
}
