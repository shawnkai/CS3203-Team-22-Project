//
// Created by Jai Lulla  on 5/2/23.
//

#include <iostream>
#include <algorithm> // For Windows

#include "ModifiesDatabaseFactory.h"

using namespace std;

/**
 * Returns a DesignAbstractionDatabase pointer, of type ModifiesDatabase, depending on the type
 * of entity that is being abstracted. A null pointer will be returned, if an invalid type of
 * entity is being abstracted.
 *
 * @param entityTypeBeingAbstracted The type of Design Entity that is being abstracted.
 * @return A DesignAbstractionDatabase pointer, of type ModifiesDatabase, relying on type of Design Entity abstracted.
 */
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
    } else if (entityTypeBeingAbstracted == "WHILE") {
        return whileStatementModifiesDatabase;
    } else if (entityTypeBeingAbstracted == "IF") {
        return ifStatementModifiesDatabase;
    }
    // add others as they are implemented (possibly wildcard?)

    // Return null pointer, in case of invalid type of entity to be abstracted.
    return nullptr;
}

/**
 * Clears all the Modifies Design Abstraction databases.
 */
void ModifiesDatabaseFactory::clearDatabase() {
    delete assignmentModifiesDatabase;
    delete readModifiesDatabase;
    delete statementModifiesDatabase;
    delete procedureModifiesDatabase;
    delete procedureCallModifiesDatabase;
    delete whileStatementModifiesDatabase;
    delete ifStatementModifiesDatabase;

    assignmentModifiesDatabase = new AssignmentModifiesDatabase();
    readModifiesDatabase = new ReadModifiesDatabase();
    statementModifiesDatabase = new StatementModifiesDatabase();
    procedureModifiesDatabase = new ProcedureModifiesDatabase();
    procedureCallModifiesDatabase = new ProcedureCallModifiesDatabase();
    whileStatementModifiesDatabase = new WhileStatementModifiesDatabase();
    ifStatementModifiesDatabase = new IfStatementModifiesDatabase();
}
