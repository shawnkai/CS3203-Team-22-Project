//
// Created by Jai Lulla  on 18/3/23.
//

#include <iostream>

#include "WhilePattern.h"

using namespace std;

WhilePattern::WhilePattern(string lineNumber, string variableName)
: Pattern(lineNumber, variableName) {

}

string WhilePattern::getTypeOfPattern() {
    return "WHILE";
}
