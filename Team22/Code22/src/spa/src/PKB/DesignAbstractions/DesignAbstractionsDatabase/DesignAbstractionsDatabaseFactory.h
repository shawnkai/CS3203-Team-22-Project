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
    // Implement the below as methods or their own Factory classes
    static DesignAbstractionDatabase* getModifiesDatabase(string entityTypeBeingExtracted);
    static DesignAbstractionDatabase* getUsesDatabase(string entityTypeBeingExtracted);
    static DesignAbstractionDatabase* getFollowsDatabase();
    static DesignAbstractionDatabase* getFollowsStarDatabase();
    static DesignAbstractionDatabase* getParentDatabase();
    static DesignAbstractionDatabase* getParentStarDatabase();

public:
    static DesignAbstractionDatabase* getAbstractionDatabase(DesignAbstraction* designAbstraction);
    static DesignAbstractionDatabase* getAbstractionDatabase(string designAbstractionType,
                                                             string entityTypeBeingAbstracted);
//    static DesignAbstractionDatabase* getAbstractionDatabase(string designAbstractionType);
};

#endif //SPA_DESIGNABSTRACTIONSDATABASEFACTORY_H
