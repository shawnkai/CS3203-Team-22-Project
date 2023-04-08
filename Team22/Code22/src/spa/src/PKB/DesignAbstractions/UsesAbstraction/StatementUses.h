//
// Created by Jai Lulla  on 15/2/23.
//

#pragma once

#ifndef SPA_STATEMENTUSES_H
#define SPA_STATEMENTUSES_H

#include <iostream>

#include "Uses.h"

using namespace std;

class StatementUses : public Uses {
public:
    explicit StatementUses(tuple<string, string, string> abstractionDetails);

    string getTypeOfAbstraction() override;
};

#endif//SPA_STATEMENTUSES_H
