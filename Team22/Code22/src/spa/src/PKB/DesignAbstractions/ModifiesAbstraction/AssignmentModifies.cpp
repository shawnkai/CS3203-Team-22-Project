//
// Created by Jai Lulla  on 5/2/23.
//

#include <iostream>

#include "AssignmentModifies.h"

using namespace std;

AssignmentModifies::AssignmentModifies(tuple<string, string, string> abstractionDetails)
    : Modifies(abstractionDetails) {
}

string AssignmentModifies::getTypeOfAbstraction() {
    return "MODIFIES:ASSIGNMENT";
}
