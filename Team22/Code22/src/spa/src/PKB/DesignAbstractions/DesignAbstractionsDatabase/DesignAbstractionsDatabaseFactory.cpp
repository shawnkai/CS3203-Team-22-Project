//
// Created by Jai Lulla  on 4/2/23.
//

#include <iostream>
#include <regex>
#include <algorithm> // For Windows

#include "DesignAbstractionsDatabaseFactory.h"

#include "PKB/Exceptions/DatabaseNotFoundException.cpp"

using namespace std;

/**
 * Returns a DesignAbstractionDatabase pointer, based on the type of Design Abstraction
 * that has been passed. A null pointer may be returned, if the passed Design Abstraction
 * details are invalid.
 *
 * @param designAbstraction The type of the Design Abstraction, whose database is to be obtained.
 * @return A DesignAbstractionDatabase pointer, based on the type of Design Abstraction passed.
 */
DesignAbstractionDatabase* DesignAbstractionsDatabaseFactory::getAbstractionDatabase(
        DesignAbstraction *designAbstraction) {
    if (regex_match(designAbstraction->getTypeOfAbstraction(), regex("MODIFIES:[0-9A-Za-z]+"))) {
        return getAbstractionDatabase("MODIFIES", designAbstraction->getEntityTypeBeingAbstracted());
    } else if (regex_match(designAbstraction->getTypeOfAbstraction(), regex("USES:[0-9A-Za-z]+"))) {
        return getAbstractionDatabase("USES", designAbstraction->getEntityTypeBeingAbstracted());
    }

    return getAbstractionDatabase(designAbstraction->getTypeOfAbstraction(), "_");
}

/**
 * Returns a DesignAbstractionDatabase pointer, based on the type of Design Abstraction,
 * and other details that has been passed. A null pointer may be returned, if the passed
 * Design Abstraction details are invalid.
 *
 * @param designAbstractionType The type of Design Abstractions, whose database is to be obtained.
 * @param entityTypeBeingAbstracted The type of the Design Entity, that is being abstracted.
 * @return A DesignAbstractionDatabase pointer, based on the type of Design Abstraction passed.
 */
DesignAbstractionDatabase* DesignAbstractionsDatabaseFactory::getAbstractionDatabase(string designAbstractionType,
                                                                                     string entityTypeBeingAbstracted) {
    transform(designAbstractionType.begin(), designAbstractionType.end(), designAbstractionType.begin(), ::toupper);

    if (designAbstractionType == "MODIFIES") {
         return getModifiesDatabase(entityTypeBeingAbstracted);
    } else if (designAbstractionType == "USES") {
        return getUsesDatabase(entityTypeBeingAbstracted);
    } else if (designAbstractionType == "FOLLOWS") {
        return followsDatabase;
    } else if (designAbstractionType == "FOLLOWSSTAR") {
        return followsStarDatabase;
    } else if (designAbstractionType == "PARENT") {
        return parentDatabase;
    } else if (designAbstractionType == "PARENTSTAR") {
        return parentStarDatabase;
    } else if (designAbstractionType == "CALLS") {
        return callsDatabase;
    } else if (designAbstractionType == "CALLSSTAR") {
        return callsStarDatabase;
    } else if (designAbstractionType == "NEXT") {
        return nextDatabase;
    } else if (designAbstractionType == "INVERSECALLS") {
        return inverseCallsDatabase;
    }

    throw DatabaseNotFoundException(("Database for " + designAbstractionType + " could not be found").data());
}

/**
 * Returns a DesignAbstractionDatabase pointer, mostly of some Modifies Abstraction database, based on
 * the type of Design Entity that is being abstracted. A null pointer may be returned, if the Design Entity
 * type passed in is invalid.
 *
 * @param entityTypeBeingAbstracted The type of Modifies database to be abstracted.
 * @return A DesignAbstractionDatabase pointer, of some Modifies Abstraction database.
 */
DesignAbstractionDatabase* DesignAbstractionsDatabaseFactory::getModifiesDatabase(string entityTypeBeingAbstracted) {
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

    throw DatabaseNotFoundException(("Database for Modifies " + entityTypeBeingAbstracted + " could not be found").data());
}

/**
 * Returns a DesignAbstractionDatabase pointer, mostly of some Uses Abstraction database, based on
 * the type of Design Entity that is being abstracted. A null pointer may be returned, if the Design Entity
 * type passed in is invalid.
 *
 * @param entityTypeBeingAbstracted The type of Uses database to be abstracted.
 * @return A DesignAbstractionDatabase pointer, of some Uses Abstraction database.
 */
DesignAbstractionDatabase* DesignAbstractionsDatabaseFactory::getUsesDatabase(string entityTypeBeingAbstracted) {
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

/**
 * Clears all the Modifies Design Abstraction databases.
 */
void DesignAbstractionsDatabaseFactory::clearModifiesDatabase() {
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

/**
 * Clears all the Uses Design Abstraction databases.
 */
void DesignAbstractionsDatabaseFactory::clearUsesDatabase() {
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

/**
 * Clears the Follows Design Abstraction database.
 */
void DesignAbstractionsDatabaseFactory::clearFollowsDatabase() {
    delete followsDatabase;

    followsDatabase = new FollowsDatabase();
}

/**
 * Clears the FollowsStar Design Abstraction database.
 */
void DesignAbstractionsDatabaseFactory::clearFollowsStarDatabase() {
    delete followsStarDatabase;

    followsStarDatabase = new FollowsStarDatabase();
}

/**
 * Clears the Parent Design Abstraction database.
 */
void DesignAbstractionsDatabaseFactory::clearParentDatabase() {
    delete parentDatabase;

    parentDatabase = new ParentDatabase();
}

/**
 * Clears the ParentStar Design Abstraction database.
 */
void DesignAbstractionsDatabaseFactory::clearParentStarDatabase() {
    delete parentStarDatabase;

    parentStarDatabase = new ParentStarDatabase();
}

/**
 * Clears the Calls Design Abstraction database.
 */
void DesignAbstractionsDatabaseFactory::clearCallsDatabase() {
    delete callsDatabase;

    callsDatabase = new CallsDatabase();
}

void DesignAbstractionsDatabaseFactory::clearCallsStarDatabase() {
    delete callsStarDatabase;

    callsStarDatabase = new CallsStarDatabase();
}

void DesignAbstractionsDatabaseFactory::clearNextDatabase() {
    delete nextDatabase;

    nextDatabase = new NextDatabase();
}

void DesignAbstractionsDatabaseFactory::clearInverseCallsDatabase() {
    delete inverseCallsDatabase;

    inverseCallsDatabase = new InverseCallsDatabase();
}

/**
 * Clears all the Design Abstraction databases.
 */
void DesignAbstractionsDatabaseFactory::clearDatabase() {
    clearModifiesDatabase();
    clearUsesDatabase();
    clearFollowsDatabase();
    clearFollowsStarDatabase();
    clearParentDatabase();
    clearParentStarDatabase();
    clearCallsDatabase();
    clearCallsStarDatabase();
    clearNextDatabase();
    clearInverseCallsDatabase();
}
