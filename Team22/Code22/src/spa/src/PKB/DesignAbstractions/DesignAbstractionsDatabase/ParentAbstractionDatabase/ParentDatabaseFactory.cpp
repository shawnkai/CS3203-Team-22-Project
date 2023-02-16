//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "ParentDatabaseFactory.h"

using namespace std;

DesignAbstractionDatabase *ParentDatabaseFactory::getParentDatabase() {
    return parentDatabase;
}
