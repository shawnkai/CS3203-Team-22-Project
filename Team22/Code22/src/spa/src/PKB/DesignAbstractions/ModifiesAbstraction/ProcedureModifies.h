//
// Created by Jai Lulla  on 5/2/23.
//

#pragma once

#ifndef SPA_PROCEDUREMODIFIES_H
#define SPA_PROCEDUREMODIFIES_H

#include <iostream>

#include "Modifies.h"

using namespace std;

class ProcedureModifies: public Modifies {
public:
    explicit ProcedureModifies(tuple<string, string, string> abstractionDetails);

    string getTypeOfAbstraction() override;
};

#endif //SPA_PROCEDUREMODIFIES_H
