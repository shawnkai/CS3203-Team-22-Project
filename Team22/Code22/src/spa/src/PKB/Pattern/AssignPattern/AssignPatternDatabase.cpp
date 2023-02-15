//
// Created by Jai Lulla  on 15/2/23.
//

#include <iostream>

#include "AssignPatternDatabase.h"

using namespace std;

bool AssignPatternDatabase::isLeftHandVariablePresentInDatabase(AssignPattern *assignPatternToBeStored) {
    return this->isLeftHandVariablePresentInDatabase(assignPatternToBeStored->getLeftHandVariableName());
}

bool AssignPatternDatabase::isLeftHandVariablePresentInDatabase(string leftHandVariableName) {
    return !((this->database.find(leftHandVariableName)) == (this->database.end()));
}

void AssignPatternDatabase::addRightHandExpressionForAnExistingVariableInDatabase(AssignPattern *assignPatternToBeStored) {
    // Simplify this

    this->database
            .find(assignPatternToBeStored->getLeftHandVariableName())->second
            ->addAdditionalRightHandExpression(
                    assignPatternToBeStored->getAllRightHandExpressions().begin()->first,
                    assignPatternToBeStored->getAllRightHandExpressions().begin()->second);

    // Maybe to save some storage, after seeing its duplicate
    delete assignPatternToBeStored;
}

void AssignPatternDatabase::addToDatabase(AssignPattern *assignPatternToBeStored) {
    if (this->isLeftHandVariablePresentInDatabase(assignPatternToBeStored)) {
        this->addRightHandExpressionForAnExistingVariableInDatabase(assignPatternToBeStored);
    } else {
        (this->database).insert(make_pair(assignPatternToBeStored->getLeftHandVariableName(), assignPatternToBeStored));
    }
}

string
AssignPatternDatabase::getRightHandExpressionOfAVariableOnAParticularLineNumberFromDatabase(string leftHandVariableName,
                                                                                            string patternLineNumber) {
    if (this->isLeftHandVariablePresentInDatabase(leftHandVariableName)) {
        // this is assuming if line number is present
        // this->getAllRightHandExpressionsOfAVariableFromDatabase(leftHandVariableName).find(patternLineNumber);

        return this->database.find(leftHandVariableName)->second->getRightHandExpressionByLineNumber(patternLineNumber);
    }

    // If not found, return empty string
    return "";
}

unordered_map<string, string> AssignPatternDatabase::getAllRightHandExpressionsOfAVariableFromDatabase(string leftHandVariableName) {
    if (this->isLeftHandVariablePresentInDatabase(leftHandVariableName)) {
        return this->database.find(leftHandVariableName)->second->getAllRightHandExpressions();
    }

    // What else to return, as left hand variable not present
    unordered_map<string, string> empty;
    return empty;
}

/**
 * Returns a vector of all the Assignment Patterns present in the database.
 * This is useful for for wildcard type queries, where left hand
 * variable parameter is a wildcard.
 *
 * @return A vector consisting of all Assignment Patterns.
 */
vector<AssignPattern*> AssignPatternDatabase::getAllRightHandExpressionsFromDatabase() {
    vector<AssignPattern*> result;

    for (auto& [patternLineNumber, assignPattern]: this->database) {
        result.push_back(assignPattern);
    }

    return result;
}
