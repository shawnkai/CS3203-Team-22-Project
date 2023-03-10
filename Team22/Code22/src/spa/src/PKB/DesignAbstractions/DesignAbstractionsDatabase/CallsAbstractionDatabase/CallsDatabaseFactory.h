//
// Created by Jai Lulla  on 6/3/23.
//

#pragma once

#ifndef SPA_CALLSDATABASEFACTORY_H
#define SPA_CALLSDATABASEFACTORY_H

#include <iostream>

#include "CallsDatabase.h"

using namespace std;

class CallsDatabaseFactory {
    static inline DesignAbstractionDatabase* callsDatabase = new CallsDatabase();

public:
    static DesignAbstractionDatabase* getCallsDatabase();

    static void clearDatabase();
};

#endif //SPA_CALLSDATABASEFACTORY_H
