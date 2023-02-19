//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "ParentDatabaseFactory.h"

using namespace std;

/**
 * Returns the database, that stores all the Parent relationships.
 *
 * @return A DesignAbstractionDatabase pointer, that points to the Parent relationship database.
 */
DesignAbstractionDatabase *ParentDatabaseFactory::getParentDatabase() {
    return parentDatabase;
}

/**
 * Clears the Parent database.
 */
void ParentDatabaseFactory::clearDatabase() {
    delete parentDatabase;

    parentDatabase = new ParentDatabase();
}
