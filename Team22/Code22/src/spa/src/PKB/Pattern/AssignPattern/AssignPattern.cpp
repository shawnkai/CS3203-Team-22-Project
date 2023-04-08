//
// Created by Jai Lulla  on 15/2/23.
//

#include <iostream>

#include "AssignPattern.h"
#include "AssignPatternDatabaseManager.h"

using namespace std;

AssignPattern::AssignPattern(string leftHandVariableName, string prefixExpression, string patternLineNumber) {
    this->leftHandVariableName = leftHandVariableName;

    // Figure out which is better, Factor: efficiency perhaps?
    //  rightHandExpressionByLineNumber[patternLineNumber] = prefixExpression;
    this->rightHandExpressionByLineNumber.insert(make_pair(patternLineNumber, prefixExpression));
}

bool AssignPattern::isLineNumberPresent(string patternLineNumber) {
    return !(this->rightHandExpressionByLineNumber.find(patternLineNumber) == this->rightHandExpressionByLineNumber.end());
}

void AssignPattern::addAdditionalRightHandExpression(string patternLineNumber, string prefixExpression) {
    this->rightHandExpressionByLineNumber.insert(make_pair(patternLineNumber, prefixExpression));
}

string AssignPattern::getLeftHandVariableName() {
    return this->leftHandVariableName;
}

string AssignPattern::getRightHandExpressionByLineNumber(string patternLineNumber) {
    return this->isLineNumberPresent(patternLineNumber) ? (this->rightHandExpressionByLineNumber.find(patternLineNumber))->second : "";
}

unordered_map<string, string> AssignPattern::getAllRightHandExpressions() {
    return this->rightHandExpressionByLineNumber;
}
