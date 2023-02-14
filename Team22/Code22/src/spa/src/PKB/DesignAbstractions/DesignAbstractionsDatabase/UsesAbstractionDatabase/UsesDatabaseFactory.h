//
// Created by Jai Lulla  on 11/2/23.
//

#pragma once

#ifndef SPA_USESDATABASEFACTORY_H
#define SPA_USESDATABASEFACTORY_H

#include <iostream>

#include "UsesDatabase.h" // Check if this is needed
#include "AssignmentUsesDatabase.h"
#include "PrintUsesDatabase.h"
#include "ProcedureUsesDatabase.h"
#include "StatementUsesDatabase.h"
#include "ProcedureCallUsesDatabase.h"

using namespace std;

class UsesDatabaseFactory {
    static inline DesignAbstractionDatabase* assignmentUsesDatabase = new AssignmentUsesDatabase();
    static inline DesignAbstractionDatabase* printUsesDatabase = new PrintUsesDatabase();
    static inline DesignAbstractionDatabase* procedureUsesDatabase = new ProcedureUsesDatabase();
    static inline DesignAbstractionDatabase* statementUsesDatabase = new StatementUsesDatabase();
    static inline DesignAbstractionDatabase* procedureCallUsesDatabase = new ProcedureCallUsesDatabase();

public:
    static DesignAbstractionDatabase* getUsesDatabase(string entityTypeBeingAbstracted);
};


#endif //SPA_USESDATABASEFACTORY_H
