//
// Created by Jai Lulla  on 4/2/23.
//

#include <iostream>

#include "Procedure.h"

using namespace std;

Procedure::Procedure(tuple<string, string> entityDetails)
: DesignEntity(entityDetails) {

}

string Procedure::getTypeOfEntity() {
    return "PROCEDURE";
}
