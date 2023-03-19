//
// Created by Jai Lulla  on 7/3/23.
//

#pragma once

#ifndef SPA_CALLSSTAR_H
#define SPA_CALLSSTAR_H

#include <iostream>

#include "PKB/DesignAbstractions/DesignAbstraction.h"

using namespace std;

class CallsStar: public DesignAbstraction {
public:
    explicit CallsStar(tuple<string, string, string> abstractionDetails);

    string getTypeOfAbstraction() override;
};

#endif //SPA_CALLSSTAR_H
