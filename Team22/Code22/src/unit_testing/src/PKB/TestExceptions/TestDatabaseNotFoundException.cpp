//
// Created by Jai Lulla  on 8/3/23.
//

#include <iostream>

#include "catch.hpp"

#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/DesignAbstractionsDatabaseFactory.h"
#include "PKB/DesignEntities/DesignEntitiesDatabase/DesignEntitiesDatabaseFactory.h"

#include "PKB/Exceptions/DatabaseNotFoundException.cpp"

using namespace std;

TEST_CASE("Test 1: Catch DatabaseNotFoundException In DesignAbstractionsDatabaseFactory") {
    bool exceptionThrown = false;

    try {
        DesignAbstractionsDatabaseFactory::getAbstractionDatabase("INVALID_ABSTRACTION_TYPE", "INVALID");
    } catch (DatabaseNotFoundException &e) {
        exceptionThrown = true;
    }

    REQUIRE(exceptionThrown);
}

TEST_CASE("Test 2: Catch DatabaseNotFoundException In DesignEntitiesDatabaseFactory") {
    bool exceptionThrown = false;

    try {
        DesignEntitiesDatabaseFactory::getEntityDatabase("INVALID_ENTITY_TYPE");
    } catch (DatabaseNotFoundException &e) {
        exceptionThrown = true;
    }

    REQUIRE(exceptionThrown);
}
