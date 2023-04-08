//
// Created by Jai Lulla  on 18/2/23.
//

#pragma once

#ifndef SPA_IFSTATEMENTMODIFIES_H
#define SPA_IFSTATEMENTMODIFIES_H

#include <iostream>

#include "StatementModifies.h"

using namespace std;

class IfStatementModifies : public StatementModifies {
public:
    explicit IfStatementModifies(tuple<string, string, string> abstractionDetails);

    string getTypeOfAbstraction() override;
};

#endif//SPA_IFSTATEMENTMODIFIES_H
