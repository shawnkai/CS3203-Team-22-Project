//
// Created by Jai Lulla  on 15/2/23.
//

#include <iostream>

#include "ProcedureCallUses.h"

using namespace std;

ProcedureCallUses::ProcedureCallUses(tuple<string, string, string> abstractionDetails)
    : Uses(abstractionDetails) {
}

string ProcedureCallUses::getTypeOfAbstraction() {
    return "USES:PROCEDURECALL";
}