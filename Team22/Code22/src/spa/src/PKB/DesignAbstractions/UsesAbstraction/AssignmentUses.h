//
// Created by Jai Lulla  on 11/2/23.
//

#pragma once

#ifndef SPA_ASSIGNMENTUSES_H
#define SPA_ASSIGNMENTUSES_H

#include <iostream>

#include "Uses.h"

using namespace std;

class AssignmentUses : public Uses {
public:
    explicit AssignmentUses(tuple<string, string, string> abstractionDetails);

    string getTypeOfAbstraction() override;
};

#endif//SPA_ASSIGNMENTUSES_H
