//
// Created by Jai Lulla  on 5/2/23.
//

#pragma once

#ifndef SPA_READSTATEMENT_H
#define SPA_READSTATEMENT_H

#include <iostream>

#include "Statement.h"

using namespace std;

class ReadStatement : public Statement {
public:
    explicit ReadStatement(tuple<string, string> entityDetails);

    string getTypeOfEntity() override;
};

#endif//SPA_READSTATEMENT_H
