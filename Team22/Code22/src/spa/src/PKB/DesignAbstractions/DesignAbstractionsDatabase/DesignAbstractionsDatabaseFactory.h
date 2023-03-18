//
// Created by Jai Lulla  on 4/2/23.
//

#pragma once

#ifndef SPA_DESIGNABSTRACTIONSDATABASEFACTORY_H
#define SPA_DESIGNABSTRACTIONSDATABASEFACTORY_H

#include <iostream>

#include "DesignAbstractionDatabase.h"

using namespace std;

class DesignAbstractionsDatabaseFactory {
    static DesignAbstractionDatabase* getModifiesDatabase(string entityTypeBeingAbstracted);
    static DesignAbstractionDatabase* getUsesDatabase(string entityTypeBeingAbstracted);
    static DesignAbstractionDatabase* getFollowsDatabase();
    static DesignAbstractionDatabase* getFollowsStarDatabase();
    static DesignAbstractionDatabase* getParentDatabase();
    static DesignAbstractionDatabase* getParentStarDatabase();
    static DesignAbstractionDatabase* getCallsDatabase();
    static DesignAbstractionDatabase* getCallsStarDatabase();
    static DesignAbstractionDatabase* getNextDatabase();
    static DesignAbstractionDatabase* getInverseCallsAbstraction();

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
