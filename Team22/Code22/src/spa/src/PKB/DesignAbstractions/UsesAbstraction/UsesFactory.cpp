//
// Created by Jai Lulla  on 11/2/23.
//

#include <iostream>
#include <algorithm> // For Windows

#include "UsesFactory.h"
#include "AssignmentUses.h"
#include "PrintUses.h"

using namespace std;

DesignAbstraction* UsesFactory::createUsesAbstraction(tuple<string, string, string> abstractionDetails) {
    string usesAbstractionType = get<0>(abstractionDetails);
    transform(usesAbstractionType.begin(), usesAbstractionType.end(), usesAbstractionType.begin(), ::toupper);

    if (usesAbstractionType == "ASSIGNMENT") {
        return new AssignmentUses(abstractionDetails);
    } else if (usesAbstractionType == "PRINT") {
        return new PrintUses(abstractionDetails);
    }

    // Temp: to pass build
    return nullptr;
}