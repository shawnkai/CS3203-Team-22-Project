//
// Created by Jai Lulla  on 5/2/23.
//

#pragma once

#ifndef SPA_MODIFIESDATABASEFACTORY_H
#define SPA_MODIFIESDATABASEFACTORY_H

#include <iostream>

#include "ModifiesDatabase.h"
#include "AssignmentModifiesDatabase.h"
#include "ReadModifiesDatabase.h"
#include "StatementModifiesDatabase.h"
#include "ProcedureModifiesDatabase.h"
#include "ProcedureCallModifiesDatabase.h"
#include "WhileStatementModifiesDatabase.h"
#include "IfStatementModifiesDatabase.h"

using namespace std;

class ModifiesDatabaseFactory {
    static inline DesignAbstractionDatabase* assignmentModifiesDatabase = new AssignmentModifiesDatabase();
    static inline DesignAbstractionDatabase* readModifiesDatabase = new ReadModifiesDatabase();
    static inline DesignAbstractionDatabase* statementModifiesDatabase = new StatementModifiesDatabase();
    static inline DesignAbstractionDatabase* procedureModifiesDatabase = new ProcedureModifiesDatabase();
    static inline DesignAbstractionDatabase* procedureCallModifiesDatabase = new ProcedureCallModifiesDatabase();
    static inline DesignAbstractionDatabase* whileStatementModifiesDatabase = new WhileStatementModifiesDatabase();
    static inline DesignAbstractionDatabase* ifStatementModifiesDatabase = new IfStatementModifiesDatabase();
    // Add more of these (possibly wildcard?)

public:
    static DesignAbstractionDatabase* getModifiesDatabase(string entityTypeBeingAbstracted);

    static void clearDatabase();
};

#endif //SPA_MODIFIESDATABASEFACTORY_H
