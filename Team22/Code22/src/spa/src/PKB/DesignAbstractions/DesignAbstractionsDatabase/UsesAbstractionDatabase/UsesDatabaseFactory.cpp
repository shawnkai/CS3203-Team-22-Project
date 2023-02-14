//
// Created by Jai Lulla  on 11/2/23.
//

#include <iostream>
#include <algorithm> // For Windows

#include "UsesDatabaseFactory.h"

using namespace std;

DesignAbstractionDatabase *UsesDatabaseFactory::getUsesDatabase(string entityTypeBeingAbstracted) {
    transform(entityTypeBeingAbstracted.begin(), entityTypeBeingAbstracted.end(), entityTypeBeingAbstracted.begin(), ::toupper);

    if (entityTypeBeingAbstracted == "ASSIGNMENT") {
        return assignmentUsesDatabase;
    } else if (entityTypeBeingAbstracted == "PRINT") {
        return printUsesDatabase;
    } else if (entityTypeBeingAbstracted == "PROCEDURE") {
        return procedureUsesDatabase;
    }

    // Temp: to pass build or throw error if not found
    return nullptr;
}
