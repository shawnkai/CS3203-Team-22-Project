//
// Created by Jai Lulla  on 9/2/23.
//

#include <iostream>

#include "PrintStatement.h"

using namespace std;

PrintStatement::PrintStatement(tuple<string, string> entityDetails)
: Statement(entityDetails) {

}

string PrintStatement::getTypeOfEntity() {
    // Make this: STATEMENT:PRINT, but remember to change usages conditions too
    // with regex or likewise
    return "PRINT";
}
