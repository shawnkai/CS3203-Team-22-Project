//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "ParentStarFactory.h"
#include "ParentStar.h"

using namespace std;

DesignAbstraction *ParentStarFactory::createParentStarAbstraction(tuple<string, string, string> abstractionDetails) {
    return new ParentStar(abstractionDetails);
}