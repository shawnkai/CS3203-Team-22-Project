//
// Created by Jai Lulla  on 9/2/23.
//

#include <iostream>

#include "Constant.h"

using namespace std;

Constant::Constant(tuple<string, string> entityDetails)
: DesignEntity(entityDetails) {

}

string Constant::getTypeOfEntity() {
    return "CONSTANT";
}
