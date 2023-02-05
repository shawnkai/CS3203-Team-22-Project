//
// Created by Jai Lulla  on 5/2/23.
//

#pragma once

#ifndef SPA_PROCEDURECALLMODIFIES_H
#define SPA_PROCEDURECALLMODIFIES_H

#include <iostream>

#include "Modifies.h"

using namespace std;

class ProcedureCallModifies: public Modifies {
public:
    explicit ProcedureCallModifies(tuple<string, string, string> abstractionDetails);

    string getTypeOfAbstraction() override;
};

#endif //SPA_PROCEDURECALLMODIFIES_H
