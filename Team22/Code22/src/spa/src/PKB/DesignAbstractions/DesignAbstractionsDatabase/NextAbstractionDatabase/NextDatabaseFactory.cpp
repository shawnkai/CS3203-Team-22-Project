//
// Created by Jai Lulla  on 8/3/23.
//

#include <iostream>

#include "NextDatabaseFactory.h"

using namespace std;

DesignAbstractionDatabase *NextDatabaseFactory::getNextDatabase() {
    return nextDatabase;
}

void NextDatabaseFactory::clearDatabase() {
    delete nextDatabase;

    nextDatabase = new NextDatabase();
}
