//
// Created by Jai Lulla  on 5/2/23.
//

#include <iostream>

#include "ProcedureModifies.h"

using namespace std;

ProcedureModifies::ProcedureModifies(tuple<string, string, string> abstractionDetails)
: Modifies(abstractionDetails) {

}

string ProcedureModifies::getTypeOfAbstraction() {
    return "MODIFIES:PROCEDURE";
}
