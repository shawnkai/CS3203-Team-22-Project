//
// Created by Jai Lulla  on 15/2/23.
//

#pragma once

#ifndef SPA_ASSIGNPATTERNDATABASEMANAGER_H
#define SPA_ASSIGNPATTERNDATABASEMANAGER_H

#include <iostream>

#include "AssignPatternDatabase.h"

using namespace std;

class AssignPatternDatabaseManager {
    static inline AssignPatternDatabase* assignPatternDatabase = new AssignPatternDatabase();

public:

    static AssignPatternDatabase* getAssignPatternDatabase();

    static void clearDatabase();
};

#endif //SPA_ASSIGNPATTERNDATABASEMANAGER_H
