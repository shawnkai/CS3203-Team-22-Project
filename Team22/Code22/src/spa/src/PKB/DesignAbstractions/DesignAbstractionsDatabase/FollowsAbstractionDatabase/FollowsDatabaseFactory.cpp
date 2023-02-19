//
// Created by Jai Lulla  on 16/2/23.
//

#include <iostream>

#include "FollowsDatabaseFactory.h"

using namespace std;

/**
 * Returns the database, that stores all the Follows relationships.
 *
 * @return A DesignAbstractionDatabase pointer, that points to the Follows relationship database.
 */
DesignAbstractionDatabase* FollowsDatabaseFactory::getFollowsDatabase() {
    return followsDatabase;
}

/**
 * Clears the Follows database.
 */
void FollowsDatabaseFactory::clearDatabase() {
    delete followsDatabase;

    followsDatabase = new FollowsDatabase();
}
