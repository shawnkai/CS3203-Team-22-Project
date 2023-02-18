//
// Created by Jai Lulla  on 18/2/23.
//

#include <iostream>

#include "WhileStatementUses.h"

using namespace std;

WhileStatementUses::WhileStatementUses(tuple<string, string, string> abstractionDetails)
: StatementUses(abstractionDetails) {

}

string WhileStatementUses::getTypeOfAbstraction() {
    return "USES:WHILE";
}
