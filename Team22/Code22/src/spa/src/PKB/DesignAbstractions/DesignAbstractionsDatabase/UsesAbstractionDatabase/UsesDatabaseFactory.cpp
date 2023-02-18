//
// Created by Jai Lulla  on 11/2/23.
//

#include <iostream>
#include <algorithm> // For Windows

#include "UsesDatabaseFactory.h"

using namespace std;

/**
 * Returns a DesignAbstractionDatabase pointer, of type UsesDatabase, depending on the type
 * of entity that is being abstracted. A null pointer will be returned, if an invalid type of
 * entity is being abstracted.
 *
 * @param entityTypeBeingAbstracted The type of Design Entity that is being abstracted.
 * @return A DesignAbstractionDatabase pointer, of type UsesDatabase, relying on type of Design Entity abstracted.
 */
DesignAbstractionDatabase *UsesDatabaseFactory::getUsesDatabase(string entityTypeBeingAbstracted) {
    transform(entityTypeBeingAbstracted.begin(), entityTypeBeingAbstracted.end(), entityTypeBeingAbstracted.begin(), ::toupper);

    if (entityTypeBeingAbstracted == "ASSIGNMENT") {
        return assignmentUsesDatabase;
    } else if (entityTypeBeingAbstracted == "PRINT") {
        return printUsesDatabase;
    } else if (entityTypeBeingAbstracted == "PROCEDURE") {
        return procedureUsesDatabase;
    } else if (entityTypeBeingAbstracted == "STATEMENT") {
        return statementUsesDatabase;
    } else if (entityTypeBeingAbstracted == "PROCEDURECALL") {
        return procedureCallUsesDatabase;
    } else if (entityTypeBeingAbstracted == "WHILE") {
        return whileStatementUsesDatabase;
    } else if (entityTypeBeingAbstracted == "IF") {
        return ifStatementUsesDatabase;
    }

    // Return null pointer, in case of invalid type of entity to be abstracted.
    return nullptr;
}
