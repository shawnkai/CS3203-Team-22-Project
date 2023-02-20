//
// Created by Jai Lulla  on 15/2/23.
//

#include <iostream>

#include "IfStatement.h"

using namespace std;

IfStatement::IfStatement(tuple<string, string> entityDetails)
: Statement(entityDetails) {

}

string IfStatement::getTypeOfEntity() {
    return "IF";
}
