//
// Created by Jai Lulla  on 5/2/23.
//

#include <iostream>

#include "ReadModifies.h"

using namespace std;

ReadModifies::ReadModifies(tuple<string, string, string> abstractionDetails)
: Modifies(abstractionDetails) {

}

string ReadModifies::getTypeOfAbstraction() {
    return "MODIFIES:READ";
}
