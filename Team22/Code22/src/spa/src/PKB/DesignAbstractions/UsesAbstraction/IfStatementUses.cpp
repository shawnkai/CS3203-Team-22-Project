//
// Created by Jai Lulla  on 18/2/23.
//

#include <iostream>

#include "IfStatementUses.h"

using namespace std;

IfStatementUses::IfStatementUses(tuple<string, string, string> abstractionDetails)
    : StatementUses(abstractionDetails) {
}

string IfStatementUses::getTypeOfAbstraction() {
    return "USES:IF";
}
