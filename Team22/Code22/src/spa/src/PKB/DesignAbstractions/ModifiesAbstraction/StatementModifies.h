//
// Created by Jai Lulla  on 5/2/23.
//

#pragma once

#ifndef SPA_STATEMENTMODIFIES_H
#define SPA_STATEMENTMODIFIES_H

#include <iostream>

#include "Modifies.h"

using namespace std;

class StatementModifies: public Modifies {
public:
    explicit StatementModifies(tuple<string, string, string> abstractionDetails);

    string getTypeOfAbstraction() override;
};


#endif //SPA_STATEMENTMODIFIES_H
