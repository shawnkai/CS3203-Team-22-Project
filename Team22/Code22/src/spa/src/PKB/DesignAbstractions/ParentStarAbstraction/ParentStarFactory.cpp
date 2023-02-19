//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "ParentStarFactory.h"
#include "ParentStar.h"

using namespace std;

/**
 * Returns a newly created ParentStar DesignAbstraction pointer, using the
 * passed in parameters.
 *
 * @param abstractionDetails The abstraction details to be captured.
 * @return A ParentStar DesignAbstraction pointer.
 */
DesignAbstraction *ParentStarFactory::createParentStarAbstraction(tuple<string, string, string> abstractionDetails) {
    return new ParentStar(abstractionDetails);
}
