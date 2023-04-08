//
// Created by Jai Lulla  on 16/2/23.
//

#include <iostream>

#include "FollowsStarFactory.h"
#include "FollowsStar.h"

/**
 * Returns a newly created FollowsStar DesignAbstraction pointer, using the
 * passed in parameters.
 *
 * @param abstractionDetails The abstraction details to be captured.
 * @return A FollowsStar DesignAbstraction pointer.
 */
DesignAbstraction *FollowsStarFactory::createFollowsStarAbstraction(tuple<string, string, string> abstractionDetails) {
    return new FollowsStar(abstractionDetails);
}

using namespace std;
