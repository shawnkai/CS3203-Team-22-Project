//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "Parent.h"
#include "ParentFactory.h"

using namespace std;

/**
 * Returns a newly created Parent DesignAbstraction pointer, using the
 * passed in parameters.
 *
 * @param abstractionDetails The abstraction details to be captured.
 * @return A Parent DesignAbstraction pointer.
 */
DesignAbstraction* ParentFactory::createParentAbstraction(tuple<string, string, string> abstractionDetails) {
    return new Parent(abstractionDetails);
}
