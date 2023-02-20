//
// Created by Jai Lulla  on 15/2/23.
//

#pragma once

#ifndef SPA_ASSIGNPATTERNDATABASEFACTORY_H
#define SPA_ASSIGNPATTERNDATABASEFACTORY_H

#include <iostream>

#include "AssignPatternDatabase.h"

using namespace std;

class AssignPatternDatabaseFactory {
    static inline AssignPatternDatabase* assignPatternDatabase = new AssignPatternDatabase();

public:

    static AssignPatternDatabase* getAssignPatternDatabase();

    static void clearDatabase();
};

#endif //SPA_ASSIGNPATTERNDATABASEFACTORY_H
