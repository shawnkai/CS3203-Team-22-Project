//
// Created by Jai Lulla  on 7/3/23.
//

#pragma once

#ifndef SPA_CALLSSTARDATABASEFACTORY_H
#define SPA_CALLSSTARDATABASEFACTORY_H

#include <iostream>

#include "CallsStarDatabase.h"

using namespace std;

class CallsStarDatabaseFactory {
    static inline DesignAbstractionDatabase* callsStarDatabase = new CallsStarDatabase();

public:
    static DesignAbstractionDatabase* getCallsStarDatabaseDatabase();

    static void clearDatabase();
};

#endif //SPA_CALLSSTARDATABASEFACTORY_H
