//
// Created by Jai Lulla  on 16/2/23.
//

#pragma once

#ifndef SPA_FOLLOWSDATABASEFACTORY_H
#define SPA_FOLLOWSDATABASEFACTORY_H

#include <iostream>

#include "FollowsDatabase.h"

using namespace std;

class FollowsDatabaseFactory {
    static inline DesignAbstractionDatabase* followsDatabase = new FollowsDatabase();

public:
    static DesignAbstractionDatabase* getFollowsDatabase();

    static void clearDatabase();
};

#endif //SPA_FOLLOWSDATABASEFACTORY_H
