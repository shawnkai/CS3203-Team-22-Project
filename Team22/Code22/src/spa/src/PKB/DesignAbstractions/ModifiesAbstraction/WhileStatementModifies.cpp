//
// Created by Jai Lulla  on 18/2/23.
//

#include <iostream>

#include "WhileStatementModifies.h"

using namespace std;

WhileStatementModifies::WhileStatementModifies(tuple<string, string, string> abstractionDetails)
    : StatementModifies(abstractionDetails) {
}

string WhileStatementModifies::getTypeOfAbstraction() {
    return "MODIFIES:WHILE";
}
