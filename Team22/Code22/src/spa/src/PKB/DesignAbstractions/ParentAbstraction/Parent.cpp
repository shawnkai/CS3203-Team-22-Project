//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "Parent.h"

using namespace std;

Parent::Parent(tuple<string, string, string> abstractionDetails)
: DesignAbstraction(abstractionDetails) {

}

string Parent::getTypeOfAbstraction() {
    return "PARENT";
}
