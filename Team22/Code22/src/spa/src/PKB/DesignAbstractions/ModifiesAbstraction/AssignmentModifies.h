//
// Created by Jai Lulla  on 5/2/23.
//

#pragma once

#ifndef SPA_ASSIGNMENTMODIFIES_H
#define SPA_ASSIGNMENTMODIFIES_H

#include <iostream>

#include "Modifies.h"

using namespace std;

class AssignmentModifies: public Modifies {
public:
    explicit AssignmentModifies(tuple<string, string, string> abstractionDetails);

    string getTypeOfAbstraction() override;
};


#endif //SPA_ASSIGNMENTMODIFIES_H
