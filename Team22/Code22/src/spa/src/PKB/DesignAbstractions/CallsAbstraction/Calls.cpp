//
// Created by Jai Lulla  on 6/3/23.
//

#include <iostream>

#include "Calls.h"

using namespace std;

Calls::Calls(tuple<string, string, string> abstractionDetails)
: DesignAbstraction(abstractionDetails) {

}

string Calls::getTypeOfAbstraction() {
    return "CALLS";
}
