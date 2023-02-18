//
// Created by Jai Lulla  on 15/2/23.
//

#include <iostream>

#include "AssignmentStatement.h"

using namespace std;

AssignmentStatement::AssignmentStatement(tuple<string, string> entityDetails)
: Statement(entityDetails) {

}

string AssignmentStatement::getTypeOfEntity() {
    return "ASSIGNMENT";
}
