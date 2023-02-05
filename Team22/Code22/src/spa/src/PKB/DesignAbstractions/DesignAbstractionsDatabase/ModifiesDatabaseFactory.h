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

using namespace std;

class ModifiesDatabaseFactory {
    static inline DesignAbstractionDatabase* assignmentModifiesDatabase = new AssignmentModifiesDatabase();
    static inline DesignAbstractionDatabase* readModifiesDatabase = new ReadModifiesDatabase();

    // Add more of these
public:
    static DesignAbstractionDatabase* getModifiesDatabase(string entityTypeBeingAbstracted);
};

#endif //SPA_MODIFIESDATABASEFACTORY_H
