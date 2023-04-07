//
// Created by Jai Lulla  on 3/2/23.
//
#pragma once

#ifndef SPA_DESIGNENTITIESDATABASEFACTORY_H
#define SPA_DESIGNENTITIESDATABASEFACTORY_H

#include <iostream>

#include "AssignmentStatementDatabase.h"
#include "CallStatementDatabase.h"
#include "ConstantDatabase.h"
#include "DesignEntityDatabase.h"
#include "IfStatementDatabase.h"
#include "PrintStatementDatabase.h"
#include "ProcedureDatabase.h"
#include "ReadStatementDatabase.h"
#include "StatementDatabase.h"
#include "VariableDatabase.h"
#include "WhileStatementDatabase.h"

using namespace std;

class DesignEntitiesDatabaseFactory {
    static inline DesignEntityDatabase *variableEntitiesDatabase = new VariableDatabase();
    static inline DesignEntityDatabase *procedureEntitiesDatabase = new ProcedureDatabase();
    static inline DesignEntityDatabase *statementEntitiesDatabase = new StatementDatabase();
    static inline DesignEntityDatabase *readStatementEntitiesDatabase = new ReadStatementDatabase();
    static inline DesignEntityDatabase *constantEntitiesDatabase = new ConstantDatabase();
    static inline DesignEntityDatabase *printStatementEntitiesDatabase = new PrintStatementDatabase();
    static inline DesignEntityDatabase *assignmentStatementEntitiesDatabase = new AssignmentStatementDatabase();
    static inline DesignEntityDatabase *callStatementEntitiesDatabase = new CallStatementDatabase();
    static inline DesignEntityDatabase *whileStatementEntitiesDatabase = new WhileStatementDatabase();
    static inline DesignEntityDatabase *ifStatementEntitiesDatabase = new IfStatementDatabase();
    // Add more as implemented

public:
    static DesignEntityDatabase *getEntityDatabase(DesignEntity *designEntity);
    static DesignEntityDatabase *getEntityDatabase(string designEntityType);

    static void clearDatabase();
};

#endif//SPA_DESIGNENTITIESDATABASEFACTORY_H
