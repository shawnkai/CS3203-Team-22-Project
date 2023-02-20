//
// Created by Jai Lulla  on 17/2/23.
//

#pragma once

#ifndef SPA_PARENTDATABASEFACTORY_H
#define SPA_PARENTDATABASEFACTORY_H

#include <iostream>

#include "ParentDatabase.h"

using namespace std;

class ParentDatabaseFactory {
    static inline DesignAbstractionDatabase* parentDatabase = new ParentDatabase();

public:
    static DesignAbstractionDatabase* getParentDatabase();

    static void clearDatabase();
};

#endif //SPA_PARENTDATABASEFACTORY_H
