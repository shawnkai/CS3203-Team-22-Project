//
// Created by Jai Lulla  on 5/2/23.
//

#include <iostream>

#include "ProcedureCallModifies.h"

using namespace std;

ProcedureCallModifies::ProcedureCallModifies(tuple<string, string, string> abstractionDetails)
: Modifies(abstractionDetails) {

}

string ProcedureCallModifies::getTypeOfAbstraction() {
    return "MODIFIES:PROCEDURECALL";
}
