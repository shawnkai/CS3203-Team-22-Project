//
// Created by Jai Lulla  on 18/2/23.
//

#pragma once

#ifndef SPA_IFSTATEMENTUSES_H
#define SPA_IFSTATEMENTUSES_H

#include <iostream>

#include "StatementUses.h"

using namespace std;

class IfStatementUses: public StatementUses {
public:
    explicit IfStatementUses(tuple<string, string, string> abstractionDetails);

    string getTypeOfAbstraction() override;
};

#endif //SPA_IFSTATEMENTUSES_H
