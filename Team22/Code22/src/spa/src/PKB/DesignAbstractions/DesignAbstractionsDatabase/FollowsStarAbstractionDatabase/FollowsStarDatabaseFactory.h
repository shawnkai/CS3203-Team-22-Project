//
// Created by Jai Lulla  on 16/2/23.
//

#pragma once

#ifndef SPA_FOLLOWSSTARDATABASEFACTORY_H
#define SPA_FOLLOWSSTARDATABASEFACTORY_H

#include <iostream>

#include "FollowsStarDatabase.h"

using namespace std;

class FollowsStarDatabaseFactory {
    static inline DesignAbstractionDatabase* followsStarDatabase = new FollowsStarDatabase();

public:
    static DesignAbstractionDatabase* getFollowsStarDatabase();

    static void clearDatabase();
};


#endif //SPA_FOLLOWSSTARDATABASEFACTORY_H
