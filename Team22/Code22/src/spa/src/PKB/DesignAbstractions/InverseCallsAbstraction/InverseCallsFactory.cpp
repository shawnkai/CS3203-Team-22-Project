//
// Created by Jai Lulla  on 17/3/23.
//

#include <iostream>

#include "InverseCalls.h"

#include "InverseCallsFactory.h"

using namespace std;
DesignAbstraction *
InverseCallsFactory::createInverseCallsAbstraction(tuple<string, string, string> abstractionDetails) {
    return new InverseCalls(abstractionDetails);
}
