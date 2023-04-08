//
// Created by Jai Lulla  on 16/2/23.
//

#include <iostream>

#include "Follows.h"


using namespace std;

Follows::Follows(tuple<string, string, string> abstractionDetails)
        : DesignAbstraction(abstractionDetails) {

}
string Follows::getTypeOfAbstraction() {
    return "FOLLOWS";
}
