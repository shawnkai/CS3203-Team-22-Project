//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "ParentStar.h"

using namespace std;

ParentStar::ParentStar(tuple<string, string, string> abstractionDetails)
    : DesignAbstraction(abstractionDetails) {
}

string ParentStar::getTypeOfAbstraction() {
    return "PARENTSTAR";
}
