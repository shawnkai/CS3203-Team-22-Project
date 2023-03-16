//
// Created by Jai Lulla  on 17/3/23.
//

#include <iostream>

#include "InverseCallsDatabaseFactory.h"

using namespace std;

DesignAbstractionDatabase *InverseCallsDatabaseFactory::getInverseCallsDatabase() {
    return inverseCallsDatabase;
}

void InverseCallsDatabaseFactory::clearDatabase() {
    delete inverseCallsDatabase;

    inverseCallsDatabase = new InverseCallsDatabase();
}
