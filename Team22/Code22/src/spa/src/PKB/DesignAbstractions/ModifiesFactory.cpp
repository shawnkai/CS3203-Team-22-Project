//
// Created by Jai Lulla  on 5/2/23.
//

#include <iostream>

#include "AssignmentModifies.h"
#include "ModifiesFactory.h"
#include "ReadModifies.h"

using namespace std;

DesignAbstraction* ModifiesFactory::createModifiesAbstraction(tuple<string, string, string> abstractionDetails) {
    // To be implemented
    // Design choice, pass 1st param as type of modifies? -> think
    // Make get<0> into var and upper case it -> do

    if (get<0>(abstractionDetails) == "ASSIGNMENT") {
        return new AssignmentModifies(abstractionDetails);
    } else if (get<0>(abstractionDetails) == "READ") {
        return new ReadModifies(abstractionDetails);
    }

    // TEMP: to pass build
    return nullptr;
}