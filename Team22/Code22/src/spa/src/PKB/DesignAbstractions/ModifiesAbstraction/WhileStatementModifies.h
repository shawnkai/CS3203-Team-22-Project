//
// Created by Jai Lulla  on 18/2/23.
//

#pragma once

#ifndef SPA_WHILESTATEMENTMODIFIES_H
#define SPA_WHILESTATEMENTMODIFIES_H

#include <iostream>

#include "StatementModifies.h"

using namespace std;

class WhileStatementModifies: public StatementModifies {
public:
    explicit WhileStatementModifies(tuple<string, string, string> abstractionDetails);

    string getTypeOfAbstraction() override;
};

#endif //SPA_WHILESTATEMENTMODIFIES_H
