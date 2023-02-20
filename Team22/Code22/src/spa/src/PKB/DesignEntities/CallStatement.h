//
// Created by Jai Lulla  on 15/2/23.
//

#pragma once

#ifndef SPA_CALLSTATEMENT_H
#define SPA_CALLSTATEMENT_H

#include <iostream>

#include "Statement.h"

using namespace std;

class CallStatement: public Statement {
public:
    explicit CallStatement(tuple<string, string> entityDetails);

    string getTypeOfEntity() override;
};

#endif //SPA_CALLSTATEMENT_H
