//
// Created by Jai Lulla  on 5/2/23.
//

#include <iostream>

#include "ReadStatement.h"

using namespace std;

ReadStatement::ReadStatement(tuple<string, string> entityDetails)
: Statement(entityDetails) {

}

string ReadStatement::getTypeOfEntity() {
    // Make this: STATEMENT:READ, but remember to change usages conditions too
    // with regex or likewise
    return "READ";
}
