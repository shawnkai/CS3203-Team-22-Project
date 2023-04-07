//
// Created by Jai Lulla  on 11/2/23.
//

#include <iostream>

#include "Uses.h"

using namespace std;

Uses::Uses(tuple<string, string, string> abstractionDetails)
    : DesignAbstraction(abstractionDetails) {
}

string Uses::getTypeOfAbstraction() {
    return "USES";
}
