//
// Created by Jai Lulla  on 5/2/23.
//

#include <iostream>

#include "StatementModifies.h"

using namespace std;

StatementModifies::StatementModifies(tuple<string, string, string> abstractionDetails)
: Modifies(abstractionDetails) {

}

string StatementModifies::getTypeOfAbstraction() {
    return "MODIFIES:STATEMENT";
}
