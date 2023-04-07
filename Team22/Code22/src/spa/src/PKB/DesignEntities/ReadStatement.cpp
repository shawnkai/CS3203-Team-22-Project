//
// Created by Jai Lulla  on 5/2/23.
//

#include <iostream>

#include "ReadStatement.h"

using namespace std;

/**
 * Creates a Read Design Entity with the given details,
 *
 * @param entityDetails This encompasses the details of the Read Entity to be created.
 */
ReadStatement::ReadStatement(tuple<string, string> entityDetails)
    : Statement(entityDetails) {
}

/**
 * Returns the type of Entity.
 *
 * @return A string stating the type of Entity.
 */
string ReadStatement::getTypeOfEntity() {
    // Make this: STATEMENT:READ, but remember to change usages conditions too
    // with regex or likewise
    return "READ";
}
