//
// Created by Jai Lulla  on 3/2/23.
//
#pragma once

#ifndef SPA_DESIGNENTITIESDATABASEFACTORY_H
#define SPA_DESIGNENTITIESDATABASEFACTORY_H

#include <iostream>

#include "DesignEntityDatabase.h"
#include "VariableDatabase.h"
#include "ProcedureDatabase.h"
#include "StatementDatabase.h"

using namespace std;

class DesignEntitiesDatabaseFactory {
    static inline DesignEntityDatabase* variableEntitiesDatabase = new VariableDatabase();
    static inline DesignEntityDatabase* procedureEntitiesDatabase = new ProcedureDatabase();
    static inline DesignEntityDatabase* statementEntitiesDatabase = new StatementDatabase();

public:

    static DesignEntityDatabase* getEntityDatabase(DesignEntity* designEntity);
    static DesignEntityDatabase* getEntityDatabase(string designEntityType);
};

#endif //SPA_DESIGNENTITIESDATABASEFACTORY_H
