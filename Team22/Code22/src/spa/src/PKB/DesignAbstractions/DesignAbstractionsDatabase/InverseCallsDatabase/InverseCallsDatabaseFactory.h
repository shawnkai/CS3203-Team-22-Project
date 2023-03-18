//
// Created by Jai Lulla  on 17/3/23.
//

#pragma once 

#ifndef SPA_INVERSECALLSDATABASEFACTORY_H
#define SPA_INVERSECALLSDATABASEFACTORY_H

#include <iostream>

#include "InverseCallsDatabase.h"

using namespace std;

class InverseCallsDatabaseFactory {
    static inline DesignAbstractionDatabase* inverseCallsDatabase = new InverseCallsDatabase();

public:
    static DesignAbstractionDatabase* getInverseCallsDatabase();

    static void clearDatabase();
};

#endif //SPA_INVERSECALLSDATABASEFACTORY_H
