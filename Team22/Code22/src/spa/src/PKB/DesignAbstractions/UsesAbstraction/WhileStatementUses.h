//
// Created by Jai Lulla  on 18/2/23.
//

#pragma once

#ifndef SPA_WHILESTATEMENTUSES_H
#define SPA_WHILESTATEMENTUSES_H

#include <iostream>

#include "StatementUses.h"

using namespace std;

class WhileStatementUses: public StatementUses {
public:
    explicit WhileStatementUses(tuple<string, string, string> abstractionDetails);

    string getTypeOfAbstraction() override;
};

#endif //SPA_WHILESTATEMENTUSES_H
