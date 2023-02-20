//
// Created by Jai Lulla  on 5/2/23.
//

#include <iostream>

#include "ReadModifies.h"

using namespace std;

/**
 * Creates a Modifies type Abstraction, considering the type
 * of Entity being Abstracted along.
 *
 * @param abstractionDetails The details of this Modifies type Abstraction.
 */
ReadModifies::ReadModifies(tuple<string, string, string> abstractionDetails)
: Modifies(abstractionDetails) {

}

/**
 * Returns the type of Abstraction.
 *
 * @return A string stating the type of Abstraction.
 */
string ReadModifies::getTypeOfAbstraction() {
    return "MODIFIES:READ";
}
