//
// Created by Jai Lulla  on 4/2/23.
//

#include <iostream>
#include <regex>
#include <algorithm> // For Windows

#include "DesignAbstractionsDatabaseFactory.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/ModifiesAbstractionDatabase/ModifiesDatabaseFactory.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/UsesAbstractionDatabase/UsesDatabaseFactory.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/FollowsAbstractionDatabase/FollowsDatabaseFactory.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/FollowsStarAbstractionDatabase/FollowsStarDatabaseFactory.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/ParentAbstractionDatabase/ParentDatabaseFactory.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/ParentStarAbstractionDatabase/ParentStarDatabaseFactory.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/CallsAbstractionDatabase/CallsDatabaseFactory.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/CallsStarAbstractionDatabase/CallsStarDatabaseFactory.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/NextAbstractionDatabase/NextDatabaseFactory.h"

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
        return getFollowsDatabase();
    } else if (designAbstractionType == "FOLLOWSSTAR") {
        return getFollowsStarDatabase();
    } else if (designAbstractionType == "PARENT") {
        return getParentDatabase();
    } else if (designAbstractionType == "PARENTSTAR") {
        return getParentStarDatabase();
    } else if (designAbstractionType == "CALLS") {
        return getCallsDatabase();
    } else if (designAbstractionType == "CALLSSTAR") {
        return getCallsStarDatabase();
    } else if (designAbstractionType == "NEXT") {
        return getNextDatabase();
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
    return ModifiesDatabaseFactory::getModifiesDatabase(entityTypeBeingAbstracted);
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
    transform(entityTypeBeingAbstracted.begin(), entityTypeBeingAbstracted.end(), entityTypeBeingAbstracted.begin(), ::toupper);
    return UsesDatabaseFactory::getUsesDatabase(entityTypeBeingAbstracted);
}

/**
 * Returns a DesignAbstractionDatabase pointer, of Follows Abstraction database.
 *
 * @return A DesignAbstractionDatabase pointer, of Follows Abstraction database.
 */
DesignAbstractionDatabase* DesignAbstractionsDatabaseFactory::getFollowsDatabase() {
    return FollowsDatabaseFactory::getFollowsDatabase();
}

/**
 * Returns a DesignAbstractionDatabase pointer, of FollowsStar Abstraction database.
 *
 * @return A DesignAbstractionDatabase pointer, of FollowsStar Abstraction database.
 */
DesignAbstractionDatabase* DesignAbstractionsDatabaseFactory::getFollowsStarDatabase() {
    return FollowsStarDatabaseFactory::getFollowsStarDatabase();
}

/**
 * Returns a DesignAbstractionDatabase pointer, of Parent Abstraction database.
 *
 * @return A DesignAbstractionDatabase pointer, of Parent Abstraction database.
 */
DesignAbstractionDatabase *DesignAbstractionsDatabaseFactory::getParentDatabase() {
    return ParentDatabaseFactory::getParentDatabase();
}

/**
 * Returns a DesignAbstractionDatabase pointer, of ParentStar Abstraction database.
 *
 * @return A DesignAbstractionDatabase pointer, of ParentStar Abstraction database.
 */
DesignAbstractionDatabase *DesignAbstractionsDatabaseFactory::getParentStarDatabase() {
    return ParentStarDatabaseFactory::getParentStarDatabase();
}

DesignAbstractionDatabase *DesignAbstractionsDatabaseFactory::getCallsDatabase() {
    return CallsDatabaseFactory::getCallsDatabase();
}

DesignAbstractionDatabase *DesignAbstractionsDatabaseFactory::getCallsStarDatabase() {
    return CallsStarDatabaseFactory::getCallsStarDatabaseDatabase();
}

DesignAbstractionDatabase *DesignAbstractionsDatabaseFactory::getNextDatabase() {
    return NextDatabaseFactory::getNextDatabase();
}

/**
 * Clears all the Modifies Design Abstraction databases.
 */
void DesignAbstractionsDatabaseFactory::clearModifiesDatabase() {
    ModifiesDatabaseFactory::clearDatabase();
}

/**
 * Clears all the Uses Design Abstraction databases.
 */
void DesignAbstractionsDatabaseFactory::clearUsesDatabase() {
    UsesDatabaseFactory::clearDatabase();
}

/**
 * Clears the Follows Design Abstraction database.
 */
void DesignAbstractionsDatabaseFactory::clearFollowsDatabase() {
    FollowsDatabaseFactory::clearDatabase();
}

/**
 * Clears the FollowsStar Design Abstraction database.
 */
void DesignAbstractionsDatabaseFactory::clearFollowsStarDatabase() {
    FollowsStarDatabaseFactory::clearDatabase();
}

/**
 * Clears the Parent Design Abstraction database.
 */
void DesignAbstractionsDatabaseFactory::clearParentDatabase() {
    ParentDatabaseFactory::clearDatabase();
}

/**
 * Clears the ParentStar Design Abstraction database.
 */
void DesignAbstractionsDatabaseFactory::clearParentStarDatabase() {
    ParentStarDatabaseFactory::clearDatabase();
}

/**
 * Clears the Calls Design Abstraction database.
 */
void DesignAbstractionsDatabaseFactory::clearCallsDatabase() {
    CallsDatabaseFactory::clearDatabase();
}

void DesignAbstractionsDatabaseFactory::clearCallsStarDatabase() {
    CallsStarDatabaseFactory::clearDatabase();
}

void DesignAbstractionsDatabaseFactory::clearNextDatabase() {
    NextDatabaseFactory::clearDatabase();
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
}
