//
// Created by Jai Lulla  on 5/2/23.
//

#include <iostream>

#include "Statement.h"

using namespace std;

/**
 * Creates a Statement Design Entity with the given details,
 *
 * @param entityDetails This encompasses the details of the Statement Entity to be created.
 */
Statement::Statement(tuple<string, string> entityDetails)
: DesignEntity(entityDetails) {

}

/**
 * Returns the type of Entity.
 *
 * @return A string stating the type of Entity.
 */
string Statement::getTypeOfEntity() {
    return "STATEMENT";
}
