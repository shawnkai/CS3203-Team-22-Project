//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "ParentStarDatabaseFactory.h"

using namespace std;

/**
 * Returns the database, that stores all the ParentStar relationships.
 *
 * @return A DesignAbstractionDatabase pointer, that points to the ParentStar relationship database.
 */
DesignAbstractionDatabase *ParentStarDatabaseFactory::getParentStarDatabase() {
    return parentStarDatabase;
}

/**
 * Clears the ParentStar database.
 */
void ParentStarDatabaseFactory::clearDatabase() {
    delete parentStarDatabase;

    parentStarDatabase = new ParentStarDatabase();
}
