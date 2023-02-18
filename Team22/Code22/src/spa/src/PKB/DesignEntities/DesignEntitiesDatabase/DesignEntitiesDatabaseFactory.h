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
#include "ReadStatementDatabase.h"
#include "ConstantDatabase.h"
#include "PrintStatementDatabase.h"
#include "AssignmentStatementDatabase.h"
#include "CallStatementDatabase.h"
#include "WhileStatementDatabase.h"
#include "IfStatementDatabase.h"

using namespace std;

class DesignEntitiesDatabaseFactory {
    static inline DesignEntityDatabase* variableEntitiesDatabase = new VariableDatabase();
    static inline DesignEntityDatabase* procedureEntitiesDatabase = new ProcedureDatabase();
    static inline DesignEntityDatabase* statementEntitiesDatabase = new StatementDatabase();
    static inline DesignEntityDatabase* readStatementEntitiesDatabase = new ReadStatementDatabase();
    static inline DesignEntityDatabase* constantEntitiesDatabase = new ConstantDatabase();
    static inline DesignEntityDatabase* printStatementEntitiesDatabase = new PrintStatementDatabase();
    static inline DesignEntityDatabase* assignmentStatementEntitiesDatabase = new AssignmentStatementDatabase();
    static inline DesignEntityDatabase* callStatementEntitiesDatabase = new CallStatementDatabase();
    static inline DesignEntityDatabase* whileStatementEntitiesDatabase = new WhileStatementDatabase();
    static inline DesignEntityDatabase* ifStatementEntitiesDatabase = new IfStatementDatabase();
    // Add more as implemented

public:

    static DesignEntityDatabase* getEntityDatabase(DesignEntity* designEntity);
    static DesignEntityDatabase* getEntityDatabase(string designEntityType);
};

#endif //SPA_DESIGNENTITIESDATABASEFACTORY_H
