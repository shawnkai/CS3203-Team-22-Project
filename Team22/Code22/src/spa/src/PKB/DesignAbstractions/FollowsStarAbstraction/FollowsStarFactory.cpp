//
// Created by Jai Lulla  on 16/2/23.
//

#include <iostream>

#include "FollowsStarFactory.h"
#include "FollowsStar.h"

using namespace std;

DesignAbstraction *FollowsStarFactory::createFollowsStarAbstraction(tuple<string, string, string> abstractionDetails) {
    return new FollowsStar(abstractionDetails);
}
