//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "ParentStarDatabaseFactory.h"

using namespace std;

DesignAbstractionDatabase *ParentStarDatabaseFactory::getParentStarDatabase() {
    return parentStarDatabase;
}
