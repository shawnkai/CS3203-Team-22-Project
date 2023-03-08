//
// Created by Jai Lulla  on 8/3/23.
//

#include <iostream>

#include "Next.h"
#include "NextFactory.h"

using namespace std;

DesignAbstraction *NextFactory::createNextAbstraction(tuple<string, string, string> abstractionDetails) {
    return new Next(abstractionDetails);
}
