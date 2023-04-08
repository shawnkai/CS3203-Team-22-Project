//
// Created by Jai Lulla  on 15/2/23.
//

#pragma once

#ifndef SPA_WHILESTATEMENT_H
#define SPA_WHILESTATEMENT_H

#include <iostream>

#include "Statement.h"

using namespace std;

class WhileStatement : public Statement {
public:
    explicit WhileStatement(tuple<string, string> entityDetails);

    string getTypeOfEntity() override;
};

#endif//SPA_WHILESTATEMENT_H
