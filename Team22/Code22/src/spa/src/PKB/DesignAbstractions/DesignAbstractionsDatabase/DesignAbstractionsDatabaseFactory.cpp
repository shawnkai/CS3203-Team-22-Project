//
// Created by Jai Lulla  on 4/2/23.
//

#include <iostream>
#include <regex>

#include "DesignAbstractionsDatabaseFactory.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/ModifiesAbstractionDatabase/ModifiesDatabaseFactory.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/UsesAbstractionDatabase/UsesDatabaseFactory.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/FollowsAbstractionDatabase/FollowsDatabaseFactory.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/FollowsStarAbstractionDatabase/FollowsStarDatabaseFactory.h"

using namespace std;

// The below one might not work
DesignAbstractionDatabase* DesignAbstractionsDatabaseFactory::getAbstractionDatabase(
        DesignAbstraction *designAbstraction) {
//    return getAbstractionDatabase(designAbstraction->getTypeOfAbstraction(),
//                                  designAbstraction->getEntityTypeBeingAbstracted());

    // Root of error here: returned null as input was "MODIFIES:ASSIGNMENT" and not "MODIFIES"
    // Possible ways to fix it:
    // 1. make all type of Modifies return "MODIFIES"
    // 2. Slice the string
    // 3. Regex, here trying that
//    if (designAbstraction->getTypeOfAbstraction() == "MODIFIES") {
//        return getModifiesDatabase(designAbstraction->getEntityTypeBeingAbstracted());
//    }

    if (regex_match(designAbstraction->getTypeOfAbstraction(), regex("MODIFIES:[0-9A-Za-z]+"))) {
        return getModifiesDatabase(designAbstraction->getEntityTypeBeingAbstracted());
    } else if (regex_match(designAbstraction->getTypeOfAbstraction(), regex("USES:[0-9A-Za-z]+"))) {
        return getUsesDatabase(designAbstraction->getEntityTypeBeingAbstracted());
    } else if (designAbstraction->getTypeOfAbstraction() == "FOLLOWS") {
        return getFollowsDatabase();
    } else if (designAbstraction->getTypeOfAbstraction() == "FOLLOWSSTAR") {
        return getFollowsStarDatabase();
    }

    // Temp: To pass build
    return nullptr;
}

DesignAbstractionDatabase* DesignAbstractionsDatabaseFactory::getAbstractionDatabase(string designAbstractionType,
                                                                                     string entityTypeBeingAbstracted) {
    // Make string toupper

    if (designAbstractionType == "MODIFIES") {
         return getModifiesDatabase(entityTypeBeingAbstracted);
    } else if (designAbstractionType == "USES") {
        return getUsesDatabase(entityTypeBeingAbstracted);
    } else if (designAbstractionType == "FOLLOWS") {
        return getFollowsDatabase();
    } else if (designAbstractionType == "FOLLOWSSTAR") {
        return getFollowsStarDatabase();
    }

    // Temp: To pass build
    return nullptr;
}

DesignAbstractionDatabase* DesignAbstractionsDatabaseFactory::getModifiesDatabase(string entityTypeBeingExtracted) {
    return ModifiesDatabaseFactory::getModifiesDatabase(entityTypeBeingExtracted);
}

DesignAbstractionDatabase* DesignAbstractionsDatabaseFactory::getUsesDatabase(string entityTypeBeingExtracted) {
    return UsesDatabaseFactory::getUsesDatabase(entityTypeBeingExtracted);
}

DesignAbstractionDatabase* DesignAbstractionsDatabaseFactory::getFollowsDatabase() {
    return FollowsDatabaseFactory::getFollowsDatabase();
}

DesignAbstractionDatabase* DesignAbstractionsDatabaseFactory::getFollowsStarDatabase() {
    return FollowsStarDatabaseFactory::getFollowsStarDatabase();
}

//DesignAbstractionDatabase* DesignAbstractionsDatabaseFactory::getAbstractionDatabase(string designAbstractionType) {
//    if (designAbstractionType == "MODIFIES") {
//        return getModifiesDatabase();
//    }
//}
