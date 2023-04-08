//
// Created by Jai Lulla  on 16/2/23.
//

#include <iostream>

#include "Follows.h"
#include "FollowsFactory.h"

/**
 * Returns a newly created Follows DesignAbstraction pointer, using the
 * passed in parameters.
 *
 * @param abstractionDetails The abstraction details to be captured.
 * @return A Follows DesignAbstraction pointer.
 */
DesignAbstraction *FollowsFactory::createFollowsAbstraction(tuple<string, string, string> abstractionDetails) {
    return new Follows(abstractionDetails);
}

using namespace std;
