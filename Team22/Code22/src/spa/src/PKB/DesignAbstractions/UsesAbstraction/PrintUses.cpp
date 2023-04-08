//
// Created by Jai Lulla  on 14/2/23.
//

#include <iostream>

#include "PrintUses.h"

using namespace std;

PrintUses::PrintUses(tuple<string, string, string> abstractionDetails)
    : Uses(abstractionDetails) {
}

string PrintUses::getTypeOfAbstraction() {
    return "USES:PRINT";
}
