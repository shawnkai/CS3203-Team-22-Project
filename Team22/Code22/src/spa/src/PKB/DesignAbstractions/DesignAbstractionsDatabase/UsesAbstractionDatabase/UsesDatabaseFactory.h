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

using namespace std;

class UsesDatabaseFactory {
    static inline DesignAbstractionDatabase* assignmentUsesDatabase = new AssignmentUsesDatabase();
    static inline DesignAbstractionDatabase* printUsesDatabase = new PrintUsesDatabase();

public:
    static DesignAbstractionDatabase* getUsesDatabase(string entityTypeBeingAbstracted);
};


#endif //SPA_USESDATABASEFACTORY_H