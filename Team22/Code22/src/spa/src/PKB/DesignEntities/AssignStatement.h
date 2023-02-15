//
// Created by Jai Lulla  on 15/2/23.
//

#pragma once

#ifndef SPA_ASSIGNSTATEMENT_H
#define SPA_ASSIGNSTATEMENT_H

#include <iostream>

#include "Statement.h"

using namespace std;

class AssignStatement: public Statement {
public:
    explicit AssignStatement(tuple<string, string> entityDetails);

    string getTypeOfEntity() override;
};

#endif //SPA_ASSIGNSTATEMENT_H
