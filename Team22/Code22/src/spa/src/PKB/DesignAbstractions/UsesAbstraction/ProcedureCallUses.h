//
// Created by Jai Lulla  on 15/2/23.
//

#pragma once

#ifndef SPA_PROCEDURECALLUSES_H
#define SPA_PROCEDURECALLUSES_H

#include <iostream>

#include "Uses.h"

using namespace std;

class ProcedureCallUses: public Uses {
public:
    explicit ProcedureCallUses(tuple<string, string, string> abstractionDetails);

    string getTypeOfAbstraction() override;
};

#endif //SPA_PROCEDURECALLUSES_H
