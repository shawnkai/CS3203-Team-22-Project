//
// Created by Jai Lulla  on 3/2/23.
//
#pragma once

#ifndef SPA_DESIGNENTITIESDATABASEFACTORY_H
#define SPA_DESIGNENTITIESDATABASEFACTORY_H

#include <iostream>

#include "DesignEntityDatabase.h"
#include "VariableDatabase.h"


using namespace std;

class DesignEntitiesDatabaseFactory {
public:
    static inline DesignEntityDatabase variableEntitiesDatabase = VariableDatabase();

    static DesignEntityDatabase getEntityDatabase(DesignEntity designEntity);
};

#endif //SPA_DESIGNENTITIESDATABASEFACTORY_H
