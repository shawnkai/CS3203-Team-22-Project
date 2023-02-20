//
// Created by Jai Lulla  on 3/2/23.
//

#include <iostream>
#include <algorithm> // For Windows

#include "DesignEntitiesDatabaseFactory.h"

using namespace std;

/**
 * Returns a DesignEntityDatabase pointer, based on the type of Design Entity that
 * has been passed in, that has to be stored. A null pointer will be returned for
 * invalid Design Entities.
 *
 * @param designEntity The Design Entity, for which the database is to be obtained.
 * @return A DesignEntityDatabase pointer, for the specified Design Entity.
 */
DesignEntityDatabase* DesignEntitiesDatabaseFactory::getEntityDatabase(DesignEntity* designEntity) {
    return getEntityDatabase(designEntity->getTypeOfEntity());
}

/**
 * Returns a DesignEntityDatabase pointer, based on the type of Design Entity that
 * has been passed in, that has to be stored. A null pointer will be returned for
 * invalid Design Entities.
 *
 * @param designEntityType The type of Design Entity, for which the database is to be obtained.
 * @return A DesignEntityDatabase pointer, for the specified Design Entity.
 */
DesignEntityDatabase* DesignEntitiesDatabaseFactory::getEntityDatabase(string designEntityType) {
    transform(designEntityType.begin(), designEntityType.end(), designEntityType.begin(), ::toupper);

    if (designEntityType == "VARIABLE") {
        return variableEntitiesDatabase;
    } else if (designEntityType == "PROCEDURE") {
        return procedureEntitiesDatabase;
    } else if (designEntityType == "STATEMENT") {
        return statementEntitiesDatabase;
    } else if (designEntityType == "READ") {
        return readStatementEntitiesDatabase;
    } else if (designEntityType == "CONSTANT") {
        return constantEntitiesDatabase;
    } else if (designEntityType == "PRINT") {
        return printStatementEntitiesDatabase;
    } else if (designEntityType == "ASSIGNMENT") {
        return assignmentStatementEntitiesDatabase;
    } else if (designEntityType == "CALL") {
        return callStatementEntitiesDatabase;
    } else if (designEntityType == "WHILE") {
        return whileStatementEntitiesDatabase;
    } else if (designEntityType == "IF") {
        return ifStatementEntitiesDatabase;
    }

    // Returning this in case of invalid Design Entity Type
    return nullptr;
}

/**
 * Clears all the Design Entity databases.
 */
void DesignEntitiesDatabaseFactory::clearDatabase() {
    delete variableEntitiesDatabase;
    delete procedureEntitiesDatabase;
    delete statementEntitiesDatabase;
    delete readStatementEntitiesDatabase;
    delete constantEntitiesDatabase;
    delete printStatementEntitiesDatabase;
    delete assignmentStatementEntitiesDatabase;
    delete callStatementEntitiesDatabase;
    delete whileStatementEntitiesDatabase;
    delete ifStatementEntitiesDatabase;

    variableEntitiesDatabase = new VariableDatabase();
    procedureEntitiesDatabase = new ProcedureDatabase();
    statementEntitiesDatabase = new StatementDatabase();
    readStatementEntitiesDatabase = new ReadStatementDatabase();
    constantEntitiesDatabase = new ConstantDatabase();
    printStatementEntitiesDatabase = new PrintStatementDatabase();
    assignmentStatementEntitiesDatabase = new AssignmentStatementDatabase();
    callStatementEntitiesDatabase = new CallStatementDatabase();
    whileStatementEntitiesDatabase = new WhileStatementDatabase();
    ifStatementEntitiesDatabase = new IfStatementDatabase();
}
