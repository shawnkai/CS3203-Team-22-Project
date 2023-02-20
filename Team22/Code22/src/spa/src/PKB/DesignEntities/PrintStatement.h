//
// Created by Jai Lulla  on 9/2/23.
//

#pragma once

#ifndef SPA_PRINTSTATEMENT_H
#define SPA_PRINTSTATEMENT_H

#include <iostream>

#include "Statement.h"

using namespace std;

class PrintStatement: public Statement {
public:
    explicit PrintStatement(tuple<string, string> entityDetails);

    string getTypeOfEntity() override;
};

#endif //SPA_PRINTSTATEMENT_H
