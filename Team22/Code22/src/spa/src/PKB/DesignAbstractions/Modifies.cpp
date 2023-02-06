//
// Created by Jai Lulla  on 5/2/23.
//

#include <iostream>

#include "Modifies.h"

using namespace std;

Modifies::Modifies(tuple<string, string, string> abstractionDetails)
: DesignAbstraction(abstractionDetails){

}

string Modifies::getTypeOfAbstraction() {
    return "MODIFIES";
}
