//
// Created by Jai Lulla  on 16/2/23.
//

#include <iostream>

#include "Follows.h"
#include "FollowsFactory.h"

using namespace std;

DesignAbstraction *FollowsFactory::createFollowsAbstraction(tuple<string, string, string> abstractionDetails) {
    return new Follows(abstractionDetails);
}
