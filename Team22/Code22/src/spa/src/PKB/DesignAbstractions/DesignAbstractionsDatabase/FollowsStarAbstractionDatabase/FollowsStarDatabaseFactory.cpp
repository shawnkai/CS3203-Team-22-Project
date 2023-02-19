//
// Created by Jai Lulla  on 16/2/23.
//

#include <iostream>

#include "FollowsStarDatabaseFactory.h"

using namespace std;

/**
 * Returns the database, that stores all the FollowsStar relationships.
 *
 * @return A DesignAbstractionDatabase pointer, that points to the FollowsStar relationship database.
 */
DesignAbstractionDatabase* FollowsStarDatabaseFactory::getFollowsStarDatabase() {
    return followsStarDatabase;
}

/**
 * Clears the FollowsStar database.
 */
void FollowsStarDatabaseFactory::clearDatabase() {
    delete followsStarDatabase;

    followsStarDatabase = new FollowsStarDatabase();
}
