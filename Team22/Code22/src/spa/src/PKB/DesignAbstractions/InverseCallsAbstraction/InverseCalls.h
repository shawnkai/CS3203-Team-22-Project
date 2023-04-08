//
// Created by Jai Lulla  on 17/3/23.
//

#pragma once

#ifndef SPA_INVERSECALLS_H
#define SPA_INVERSECALLS_H

#include <iostream>


#include "PKB/DesignAbstractions/DesignAbstraction.h"
using namespace std;

class InverseCalls: public DesignAbstraction {
public:
    explicit InverseCalls(tuple<string, string, string> abstractionDetails);

    string getTypeOfAbstraction() override;
};

#endif //SPA_INVERSECALLS_H
