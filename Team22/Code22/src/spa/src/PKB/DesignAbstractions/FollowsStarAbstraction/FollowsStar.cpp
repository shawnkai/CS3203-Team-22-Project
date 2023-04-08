//
// Created by Jai Lulla  on 16/2/23.
//

#include <iostream>

#include "FollowsStar.h"

using namespace std;

FollowsStar::FollowsStar(tuple<string, string, string> abstractionDetails)

        : DesignAbstraction(abstractionDetails) {
}

string FollowsStar::getTypeOfAbstraction() {
    return "FOLLOWSSTAR";
}
