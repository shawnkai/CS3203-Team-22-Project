//
// Created by Jai Lulla  on 4/2/23.
//

#include <iostream>

#include "Procedure.h"

using namespace std;

/**
 * Creates a Procedure Design Entity with the given details,
 *
 * @param entityDetails This encompasses the details of the Procedure Entity to be created.
 */
Procedure::Procedure(tuple<string, string> entityDetails)
: DesignEntity(entityDetails) {

}

/**
 * Returns the type of Entity.
 *
 * @return A string stating the type of Entity.
 */
string Procedure::getTypeOfEntity() {
    return "PROCEDURE";
}
