//
// Created by Jai Lulla  on 7/3/23.
//

#include <iostream>

#include "CallsStar.h"

using namespace std;

CallsStar::CallsStar(tuple<string, string, string> abstractionDetails)
    : DesignAbstraction(abstractionDetails) {
}

string CallsStar::getTypeOfAbstraction() {
    return "CALLSSTAR";
}
