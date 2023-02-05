//
// Created by Jai Lulla  on 4/2/23.
//

#include <iostream>
#include <regex>

#include "DesignAbstractionsDatabaseFactory.h"
#include "ModifiesDatabaseFactory.h"

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
    }


    // Temp: To pass build
    return nullptr;
}

DesignAbstractionDatabase* DesignAbstractionsDatabaseFactory::getAbstractionDatabase(string designAbstractionType,
                                                                                     string entityTypeBeingAbstracted) {
    // Make string toupper

    if (designAbstractionType == "MODIFIES") {
        // Caused Error
         return getModifiesDatabase(entityTypeBeingAbstracted);
    }

    // Temp: To pass build
    return nullptr;
}

DesignAbstractionDatabase* DesignAbstractionsDatabaseFactory::getModifiesDatabase(string entityTypeBeingExtracted) {
    return ModifiesDatabaseFactory::getModifiesDatabase(entityTypeBeingExtracted);

    // Temp: To pass build
    return nullptr;
}

DesignAbstractionDatabase* DesignAbstractionsDatabaseFactory::getUsesDatabase(string entityTypeBeingExtracted) {
    // Temp: To pass build
    return nullptr;
}

//DesignAbstractionDatabase* DesignAbstractionsDatabaseFactory::getAbstractionDatabase(string designAbstractionType) {
//    if (designAbstractionType == "MODIFIES") {
//        return getModifiesDatabase();
//    }
//}
