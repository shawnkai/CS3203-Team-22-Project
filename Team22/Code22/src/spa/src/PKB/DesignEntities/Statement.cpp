//
// Created by Jai Lulla  on 5/2/23.
//

#include <iostream>

#include "Statement.h"

using namespace std;

Statement::Statement(tuple<string, string> entityDetails)
: DesignEntity(entityDetails) {

}

string Statement::getTypeOfEntity() {
    return "STATEMENT";
}
