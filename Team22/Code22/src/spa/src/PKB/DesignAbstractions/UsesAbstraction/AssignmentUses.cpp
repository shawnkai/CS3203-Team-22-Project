//
// Created by Jai Lulla  on 11/2/23.
//

#include <iostream>

#include "AssignmentUses.h"

using namespace std;

AssignmentUses::AssignmentUses(tuple<string, string, string> abstractionDetails)
: Uses(abstractionDetails) {

}

string AssignmentUses::getTypeOfAbstraction() {
    return "USES:ASSIGNMENT";
}
