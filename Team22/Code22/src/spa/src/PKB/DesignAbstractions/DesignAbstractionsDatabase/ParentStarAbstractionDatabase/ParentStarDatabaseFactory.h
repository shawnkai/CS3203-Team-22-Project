//
// Created by Jai Lulla  on 17/2/23.
//

#pragma once

#ifndef SPA_PARENTSTARDATABASEFACTORY_H
#define SPA_PARENTSTARDATABASEFACTORY_H

#include <iostream>

#include "ParentStarDatabase.h"

using namespace std;

class ParentStarDatabaseFactory {
    static inline DesignAbstractionDatabase* parentStarDatabase = new ParentStarDatabase();

public:
    static DesignAbstractionDatabase* getParentStarDatabase();

    static void clearDatabase();
};

#endif //SPA_PARENTSTARDATABASEFACTORY_H
