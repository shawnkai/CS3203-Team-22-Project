//
// Created by Jai Lulla  on 6/3/23.
//

#include <iostream>

#include "CallsDatabaseFactory.h"

using namespace std;

DesignAbstractionDatabase *CallsDatabaseFactory::getCallsDatabase() {
    return callsDatabase;
}

void CallsDatabaseFactory::clearDatabase() {
    delete callsDatabase;

    callsDatabase = new CallsDatabase();
}
