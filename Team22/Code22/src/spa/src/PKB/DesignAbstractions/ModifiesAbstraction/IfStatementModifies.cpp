//
// Created by Jai Lulla  on 18/2/23.
//

#include <iostream>

#include "IfStatementModifies.h"

using namespace std;

IfStatementModifies::IfStatementModifies(tuple<string, string, string> abstractionDetails)
    : StatementModifies(abstractionDetails) {
}

string IfStatementModifies::getTypeOfAbstraction() {
    return "MODIFIES:IF";
}
