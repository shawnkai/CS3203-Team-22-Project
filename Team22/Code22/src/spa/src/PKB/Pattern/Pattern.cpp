//
// Created by Jai Lulla  on 18/3/23.
//

#include <iostream>

#include "Pattern.h"

using namespace std;

Pattern::Pattern(string lineNumber, string variableName) {
    this->lineNumber = lineNumber;
    this->variableNamesUsed.insert(variableName);
}

void Pattern::addAdditionalVariableOnLine(string variableName) {
    this->variableNamesUsed.insert(variableName);
}

bool Pattern::isVariableNamePresent(string variableName) {
    return (!(this->variableNamesUsed.find(variableName) == this->variableNamesUsed.end()));
}

string Pattern::getLineNumber() {
    return this->lineNumber;
}

unordered_set<string> Pattern::getVariableNamesUsed() {
    return this->variableNamesUsed;
}
