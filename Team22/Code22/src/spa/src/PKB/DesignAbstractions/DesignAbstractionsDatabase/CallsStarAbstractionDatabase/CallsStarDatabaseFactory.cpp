//
// Created by Jai Lulla  on 7/3/23.
//

#include <iostream>

#include "CallsStarDatabaseFactory.h"

using namespace std;

DesignAbstractionDatabase *CallsStarDatabaseFactory::getCallsStarDatabaseDatabase() {
    return callsStarDatabase;
}

void CallsStarDatabaseFactory::clearDatabase() {
    delete callsStarDatabase;

    callsStarDatabase = new CallsStarDatabase();
}
