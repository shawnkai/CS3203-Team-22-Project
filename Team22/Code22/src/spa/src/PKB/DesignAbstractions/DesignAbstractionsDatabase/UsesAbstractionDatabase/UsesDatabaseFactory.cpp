//
// Created by Jai Lulla  on 11/2/23.
//

#include <iostream>
#include <algorithm> // For Windows

#include "UsesDatabaseFactory.h"

#include "PKB/Exceptions/DatabaseNotFoundException.cpp"

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

    throw DatabaseNotFoundException(("Database for Uses " + entityTypeBeingAbstracted + " could not be found").data());
}

void UsesDatabaseFactory::clearDatabase() {
    delete assignmentUsesDatabase;
    delete printUsesDatabase;
    delete procedureUsesDatabase;
    delete statementUsesDatabase;
    delete procedureCallUsesDatabase;
    delete whileStatementUsesDatabase;
    delete ifStatementUsesDatabase;

    assignmentUsesDatabase = new AssignmentUsesDatabase();
    printUsesDatabase = new PrintUsesDatabase();
    procedureUsesDatabase = new ProcedureUsesDatabase();
    statementUsesDatabase = new StatementUsesDatabase();
    procedureCallUsesDatabase = new ProcedureCallUsesDatabase();
    whileStatementUsesDatabase = new WhileStatementUsesDatabase();
    ifStatementUsesDatabase = new IfStatementUsesDatabase();
}
