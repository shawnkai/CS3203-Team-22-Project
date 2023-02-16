//
// Created by Jai Lulla  on 16/2/23.
//

#include <iostream>

#include "FollowsDatabaseFactory.h"

using namespace std;

DesignAbstractionDatabase* FollowsDatabaseFactory::getFollowsDatabase() {
    return followsDatabase;
}
