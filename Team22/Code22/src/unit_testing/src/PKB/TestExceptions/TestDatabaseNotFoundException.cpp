//
// Created by Jai Lulla  on 8/3/23.
//

#include <iostream>

#include "catch.hpp"

#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/DesignAbstractionsDatabaseFactory.h"
#include "PKB/DesignEntities/DesignEntitiesDatabase/DesignEntitiesDatabaseFactory.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/ModifiesAbstractionDatabase/ModifiesDatabaseFactory.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/UsesAbstractionDatabase/UsesDatabaseFactory.h"

#include "PKB/Exceptions/DatabaseNotFoundException.cpp"

using namespace std;

TEST_CASE("Test 1: Catch DatabaseNotFoundException In DesignAbstractionsDatabaseFactory", "[!throws][!shouldfail]") {
    DesignAbstractionsDatabaseFactory::getAbstractionDatabase("INVALID_ABSTRACTION_TYPE", "INVALID");
}

TEST_CASE("Test 2: Catch DatabaseNotFoundException In DesignEntitiesDatabaseFactory", "[!throws][!shouldfail]") {
    DesignEntitiesDatabaseFactory::getEntityDatabase("INVALID_ENTITY_TYPE");
}

TEST_CASE("Test 3: Catch DatabaseNotFoundException In ModifiesDatabaseFactory", "[!throws][!shouldfail]") {
    ModifiesDatabaseFactory::getModifiesDatabase("INVALID_MODIFIES_ABSTRACTION_TYPE");
}

TEST_CASE("Test 4: Catch DatabaseNotFoundException In UsesDatabaseFactory", "[!throws][!shouldfail]") {
    UsesDatabaseFactory::getUsesDatabase("INVALID_MODIFIES_ABSTRACTION_TYPE");
}
