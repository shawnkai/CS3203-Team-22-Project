//
// Created by Jai Lulla  on 15/2/23.
//

#pragma once

#ifndef SPA_IFSTATEMENT_H
#define SPA_IFSTATEMENT_H

#include <iostream>

#include "Statement.h"

using namespace std;

class IfStatement: public Statement {
public:
    explicit IfStatement(tuple<string, string> entityDetails);

    string getTypeOfEntity() override;
};

#endif //SPA_IFSTATEMENT_H
