//
// Created by Jai Lulla  on 5/2/23.
//

#include <iostream>

#include "ModifiesDatabaseFactory.h"

using namespace std;

DesignAbstractionDatabase *ModifiesDatabaseFactory::getModifiesDatabase(string entityTypeBeingAbstracted) {
    transform(entityTypeBeingAbstracted.begin(), entityTypeBeingAbstracted.end(), entityTypeBeingAbstracted.begin(), ::toupper);

    if (entityTypeBeingAbstracted == "ASSIGNMENT") {
        return assignmentModifiesDatabase;
    } else if (entityTypeBeingAbstracted == "READ") {
        return readModifiesDatabase;
    }
    // add others as they are implemented


    // Temp: to pass build
    return nullptr;
}
