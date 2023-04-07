//
// Created by Jai Lulla  on 14/3/23.
//

#pragma once

#ifndef SPA_CONTROLFLOWGRAPHDATABASEMANAGER_H
#define SPA_CONTROLFLOWGRAPHDATABASEMANAGER_H

#include <iostream>

#include "ControlFlowGraphDatabase.h"

using namespace std;

class ControlFlowGraphDatabaseManager {
    static inline ControlFlowGraphDatabase* controlFlowGraphDatabase = new ControlFlowGraphDatabase();

public:
    static ControlFlowGraphDatabase* getControlFlowGraphDatabase();

    static void clearDatabase();
};

#endif //SPA_CONTROLFLOWGRAPHDATABASEMANAGER_H
