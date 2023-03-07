//
// Created by Jai Lulla  on 6/3/23.
//

#include <iostream>

#include "Calls.h"
#include "CallsFactory.h"

using namespace std;

DesignAbstraction *CallsFactory::createCallsAbstraction(tuple<string, string, string> abstractionDetails) {
    return new Calls(abstractionDetails);
}
