//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "Parent.h"
#include "ParentFactory.h"

using namespace std;

DesignAbstraction* ParentFactory::createParentAbstraction(tuple<string, string, string> abstractionDetails) {
    return new Parent(abstractionDetails);
}
