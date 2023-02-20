//
// Created by Jai Lulla  on 15/2/23.
//

#include <iostream>

#include "ProcedureUses.h"

using namespace std;

ProcedureUses::ProcedureUses(tuple<string, string, string> abstractionDetails)
: Uses(abstractionDetails) {

}

string ProcedureUses::getTypeOfAbstraction() {
    return "USES:PROCEDURE";
}
