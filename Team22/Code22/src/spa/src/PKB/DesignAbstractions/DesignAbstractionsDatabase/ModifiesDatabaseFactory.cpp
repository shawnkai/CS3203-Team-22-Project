//
// Created by Jai Lulla  on 5/2/23.
//

#include <iostream>
#include <algorithm>

#include "ModifiesDatabaseFactory.h"

using namespace std;

DesignAbstractionDatabase *ModifiesDatabaseFactory::getModifiesDatabase(string entityTypeBeingAbstracted) {
    transform(entityTypeBeingAbstracted.begin(), entityTypeBeingAbstracted.end(), entityTypeBeingAbstracted.begin(), ::toupper);

    if (entityTypeBeingAbstracted == "ASSIGNMENT") {
        return assignmentModifiesDatabase;
    } else if (entityTypeBeingAbstracted == "READ") {
        return readModifiesDatabase;
    } else if (entityTypeBeingAbstracted == "STATEMENT") {
        return statementModifiesDatabase;
    } else if (entityTypeBeingAbstracted == "PROCEDURE") {
        return procedureModifiesDatabase;
    } else if (entityTypeBeingAbstracted == "PROCEDURECALL") {
        return procedureCallModifiesDatabase;
    }
    // add others as they are implemented (possibly wildcard?)

    // Temp: to pass build or throw error if not found
    return nullptr;
}
