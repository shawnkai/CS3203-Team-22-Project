//
// Created by Jai Lulla  on 7/3/23.
//

#include <iostream>

#include "CallsStar.h"
#include "CallsStarFactory.h"

using namespace std;

DesignAbstraction *CallsStarFactory::createCallsStarAbstraction(tuple<string, string, string> abstractionDetails) {
    return new CallsStar(abstractionDetails);
}
