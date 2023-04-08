//
// Created by Jai Lulla  on 15/2/23.
//

#include <iostream>

#include "WhileStatement.h"

using namespace std;

WhileStatement::WhileStatement(tuple<string, string> entityDetails)
    : Statement((entityDetails)) {
}

string WhileStatement::getTypeOfEntity() {
    return "WHILE";
}