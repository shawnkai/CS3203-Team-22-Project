//
// Created by Jai Lulla  on 3/2/23.
//

#include <iostream>

#include "Variable.h"

using namespace std;

Variable::Variable(tuple<string, string> entityDetails)
: DesignEntity(entityDetails) {

}

string Variable::getTypeOfEntity() {
    return "VARIABLE";
}
