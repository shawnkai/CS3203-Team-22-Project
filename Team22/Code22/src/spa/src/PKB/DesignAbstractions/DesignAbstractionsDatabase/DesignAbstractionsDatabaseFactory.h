//
// Created by Jai Lulla  on 4/2/23.
//

#pragma once

#ifndef SPA_DESIGNABSTRACTIONSDATABASEFACTORY_H
#define SPA_DESIGNABSTRACTIONSDATABASEFACTORY_H

#include <iostream>

#include "DesignAbstractionDatabase.h"

#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/CallsAbstractionDatabase/CallsDatabase.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/CallsStarAbstractionDatabase/CallsStarDatabase.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/FollowsAbstractionDatabase/FollowsDatabase.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/FollowsStarAbstractionDatabase/FollowsStarDatabase.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/InverseCallsDatabase/InverseCallsDatabase.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/NextAbstractionDatabase/NextDatabase.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/ParentAbstractionDatabase/ParentDatabase.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/ParentStarAbstractionDatabase/ParentStarDatabase.h"

#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/ModifiesAbstractionDatabase/AssignmentModifiesDatabase.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/ModifiesAbstractionDatabase/ReadModifiesDatabase.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/ModifiesAbstractionDatabase/StatementModifiesDatabase.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/ModifiesAbstractionDatabase/ProcedureModifiesDatabase.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/ModifiesAbstractionDatabase/ProcedureCallModifiesDatabase.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/ModifiesAbstractionDatabase/WhileStatementModifiesDatabase.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/ModifiesAbstractionDatabase/IfStatementModifiesDatabase.h"

#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/UsesAbstractionDatabase/AssignmentUsesDatabase.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/UsesAbstractionDatabase/PrintUsesDatabase.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/UsesAbstractionDatabase/ProcedureUsesDatabase.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/UsesAbstractionDatabase/StatementUsesDatabase.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/UsesAbstractionDatabase/WhileStatementUsesDatabase.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/UsesAbstractionDatabase/ProcedureCallUsesDatabase.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/UsesAbstractionDatabase/IfStatementUsesDatabase.h"

using namespace std;

class DesignAbstractionsDatabaseFactory {
    static inline DesignAbstractionDatabase* callsDatabase = new CallsDatabase();
    static inline DesignAbstractionDatabase* callsStarDatabase = new CallsStarDatabase();
    static inline DesignAbstractionDatabase* followsDatabase = new FollowsDatabase();
    static inline DesignAbstractionDatabase* followsStarDatabase = new FollowsStarDatabase();
    static inline DesignAbstractionDatabase* inverseCallsDatabase = new InverseCallsDatabase();
    static inline DesignAbstractionDatabase* nextDatabase = new NextDatabase();
    static inline DesignAbstractionDatabase* parentDatabase = new ParentDatabase();
    static inline DesignAbstractionDatabase* parentStarDatabase = new ParentStarDatabase();

    static inline DesignAbstractionDatabase* assignmentModifiesDatabase = new AssignmentModifiesDatabase();
    static inline DesignAbstractionDatabase* readModifiesDatabase = new ReadModifiesDatabase();
    static inline DesignAbstractionDatabase* statementModifiesDatabase = new StatementModifiesDatabase();
    static inline DesignAbstractionDatabase* procedureModifiesDatabase = new ProcedureModifiesDatabase();
    static inline DesignAbstractionDatabase* procedureCallModifiesDatabase = new ProcedureCallModifiesDatabase();
    static inline DesignAbstractionDatabase* whileStatementModifiesDatabase = new WhileStatementModifiesDatabase();
    static inline DesignAbstractionDatabase* ifStatementModifiesDatabase = new IfStatementModifiesDatabase();

    static inline DesignAbstractionDatabase* assignmentUsesDatabase = new AssignmentUsesDatabase();
    static inline DesignAbstractionDatabase* printUsesDatabase = new PrintUsesDatabase();
    static inline DesignAbstractionDatabase* procedureUsesDatabase = new ProcedureUsesDatabase();
    static inline DesignAbstractionDatabase* statementUsesDatabase = new StatementUsesDatabase();
    static inline DesignAbstractionDatabase* procedureCallUsesDatabase = new ProcedureCallUsesDatabase();
    static inline DesignAbstractionDatabase* whileStatementUsesDatabase = new WhileStatementUsesDatabase();
    static inline DesignAbstractionDatabase* ifStatementUsesDatabase = new IfStatementUsesDatabase();

    static DesignAbstractionDatabase* getModifiesDatabase(string entityTypeBeingAbstracted);
    static DesignAbstractionDatabase* getUsesDatabase(string entityTypeBeingAbstracted);

    static void clearModifiesDatabase();
    static void clearUsesDatabase();
    static void clearFollowsDatabase();
    static void clearFollowsStarDatabase();
    static void clearParentDatabase();
    static void clearParentStarDatabase();
    static void clearCallsDatabase();
    static void clearCallsStarDatabase();
    static void clearNextDatabase();
    static void clearInverseCallsDatabase();

public:
    static DesignAbstractionDatabase* getAbstractionDatabase(DesignAbstraction* designAbstraction);
    static DesignAbstractionDatabase* getAbstractionDatabase(string designAbstractionType,
                                                             string entityTypeBeingAbstracted);

    static void clearDatabase();
};

#endif //SPA_DESIGNABSTRACTIONSDATABASEFACTORY_H
