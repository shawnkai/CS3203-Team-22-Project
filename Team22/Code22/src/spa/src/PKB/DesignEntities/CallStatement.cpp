//
// Created by Jai Lulla  on 15/2/23.
//

#include <iostream>

#include "CallStatement.h"

using namespace std;

CallStatement::CallStatement(tuple<string, string> entityDetails)
    : Statement(entityDetails) {
}

string CallStatement::getTypeOfEntity() {
    return "CALL";
}
