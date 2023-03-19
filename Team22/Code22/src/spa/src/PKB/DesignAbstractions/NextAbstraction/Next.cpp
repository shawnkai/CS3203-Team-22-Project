//
// Created by Jai Lulla  on 8/3/23.
//

#include <iostream>

#include "Next.h"

using namespace std;

Next::Next(tuple<string, string, string> abstractionDetails)
: DesignAbstraction(abstractionDetails) {

}

string Next::getTypeOfAbstraction() {
    return "NEXT";
}
