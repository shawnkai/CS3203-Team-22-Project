//
// Created by Jai Lulla  on 15/2/23.
//

#include <iostream>

#include "AssignStatement.h"

using namespace std;

AssignStatement::AssignStatement(tuple<string, string> entityDetails)
: Statement(entityDetails) {

}

string AssignStatement::getTypeOfEntity() {
    return "ASSIGN";
}
