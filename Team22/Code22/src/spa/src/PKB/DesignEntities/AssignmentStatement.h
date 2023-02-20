//
// Created by Jai Lulla  on 15/2/23.
//

#pragma once

#ifndef SPA_ASSIGNMENTSTATEMENT_H
#define SPA_ASSIGNMENTSTATEMENT_H

#include <iostream>

#include "Statement.h"

using namespace std;

class AssignmentStatement: public Statement {
public:
    explicit AssignmentStatement(tuple<string, string> entityDetails);

    string getTypeOfEntity() override;
};

#endif //SPA_ASSIGNMENTSTATEMENT_H
