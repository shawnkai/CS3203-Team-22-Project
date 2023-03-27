//
// Created by Jai Lulla  on 14/3/23.
//

#pragma once

#ifndef SPA_CONTROLFLOWGRAPHDATABASEFACTORY_H
#define SPA_CONTROLFLOWGRAPHDATABASEFACTORY_H

#include <iostream>

#include "ControlFlowGraphDatabase.h"

using namespace std;

class ControlFlowGraphDatabaseFactory {
    static inline ControlFlowGraphDatabase* controlFlowGraphDatabase = new ControlFlowGraphDatabase();

public:
    static ControlFlowGraphDatabase* getControlFlowGraphDatabase();

    static void clearDatabase();
};

#endif //SPA_CONTROLFLOWGRAPHDATABASEFACTORY_H
