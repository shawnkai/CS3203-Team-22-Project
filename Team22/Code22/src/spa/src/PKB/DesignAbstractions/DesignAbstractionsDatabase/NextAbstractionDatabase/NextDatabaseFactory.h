//
// Created by Jai Lulla  on 8/3/23.
//

#pragma once

#ifndef SPA_NEXTDATABASEFACTORY_H
#define SPA_NEXTDATABASEFACTORY_H

#include <iostream>

#include "NextDatabase.h"

using namespace std;

class NextDatabaseFactory {
    static inline DesignAbstractionDatabase* nextDatabase = new NextDatabase();

public:
    static DesignAbstractionDatabase* getNextDatabase();

    static void clearDatabase();
};

#endif //SPA_NEXTDATABASEFACTORY_H
