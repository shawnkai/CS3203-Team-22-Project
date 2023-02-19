//
// Created by Jai Lulla  on 16/2/23.
//

#include <iostream>

#include "FollowsStarDatabaseFactory.h"

using namespace std;

DesignAbstractionDatabase* FollowsStarDatabaseFactory::getFollowsStarDatabase() {
    return followsStarDatabase;
}

void FollowsStarDatabaseFactory::clearDatabase() {
    delete followsStarDatabase;

    followsStarDatabase = new FollowsStarDatabase();
}
