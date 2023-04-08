//
// Created by Jai Lulla  on 15/2/23.
//

#pragma once

#ifndef SPA_PROCEDUREUSES_H
#define SPA_PROCEDUREUSES_H

#include <iostream>

#include "Uses.h"

using namespace std;

class ProcedureUses : public Uses {
public:
    explicit ProcedureUses(tuple<string, string, string> abstractionDetails);

    string getTypeOfAbstraction() override;
};

#endif//SPA_PROCEDUREUSES_H
