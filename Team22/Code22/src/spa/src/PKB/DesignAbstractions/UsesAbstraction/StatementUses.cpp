//
// Created by Jai Lulla  on 15/2/23.
//

#include <iostream>

#include "StatementUses.h"

using namespace std;

StatementUses::StatementUses(tuple<string, string, string> abstractionDetails)
: Uses(abstractionDetails) {

}

string StatementUses::getTypeOfAbstraction() {
    return "USES:STATEMENT";
}
