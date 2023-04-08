//
// Created by Jai Lulla  on 17/3/23.
//

#include <iostream>

#include "InverseCalls.h"

using namespace std;

InverseCalls::InverseCalls(tuple<string, string, string> abstractionDetails)

        : DesignAbstraction(abstractionDetails) {
}

string InverseCalls::getTypeOfAbstraction() {
    return "INVERSECALLS";
}
