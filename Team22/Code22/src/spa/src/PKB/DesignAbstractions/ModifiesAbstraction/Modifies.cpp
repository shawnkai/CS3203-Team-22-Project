//
// Created by Jai Lulla  on 5/2/23.
//

#include <iostream>

#include "Modifies.h"

using namespace std;

/**
 * Creates a Modifies type Abstraction.
 *
 * @param abstractionDetails The details of this Modifies type Abstraction.
 */
Modifies::Modifies(tuple<string, string, string> abstractionDetails)
    : DesignAbstraction(abstractionDetails) {
}

/**
 * Returns the type of Abstraction.
 *
 * @return A string stating the type of Abstraction.
 */
string Modifies::getTypeOfAbstraction() {
    return "MODIFIES";
}
