//
// Created by Jai Lulla  on 3/2/23.
//

#include <iostream>

#include "Variable.h"

using namespace std;

Variable::Variable(tuple<string, string> entityDetails)
: DesignEntity(entityDetails) {
//    this->nameOfEntity = get<0>(entityDetails);
//    (this->occurrenceOfEntity).push_back(get<1>(entityDetails));
}

string Variable::getTypeOfEntity() {
    return "VARIABLE";
}
