//
// Created by Jai Lulla  on 3/2/23.
//

#include <iostream>

#include "Variable.h"

using namespace std;

/**
 * Creates a Variable Design Entity with the given details,
 *
 * @param entityDetails This encompasses the details of the Variable Entity to be created.
 */
Variable::Variable(tuple<string, string> entityDetails)
: DesignEntity(entityDetails) {

}

/**
 * Returns the type of Entity.
 *
 * @return A string stating the type of Entity.
 */
string Variable::getTypeOfEntity() {
    return "VARIABLE";
}
