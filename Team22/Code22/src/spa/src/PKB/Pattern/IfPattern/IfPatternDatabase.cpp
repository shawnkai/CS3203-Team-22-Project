//
// Created by Jai Lulla  on 18/3/23.
//

#include <iostream>

#include "IfPatternDatabase.h"

#include "PKB/Exceptions/InvalidPatternTypeException.cpp"

using namespace std;

bool IfPatternDatabase::isValidPatternType(Pattern *patternToBeStored) {
    IfPattern* ifPatternToBeStored = dynamic_cast<IfPattern*>(patternToBeStored);

    if (ifPatternToBeStored == nullptr) {
        return false;
    }

    return true;
}

bool IfPatternDatabase::isLineNumberPresent(string lineNumber) {
    return (this->database.find(lineNumber) != this->database.end());
}

void IfPatternDatabase::updatePatternInDatabase(Pattern* patternToBeStored) {
    if (!(this->isValidPatternType(patternToBeStored))) {
        // Throw Error
        throw InvalidPatternTypeException(
                ("Got: " + patternToBeStored->getTypeOfPattern() + ". Expected: IfPattern Type Here").data());
    }

    IfPattern* ifPatternToBeStored = dynamic_cast<IfPattern*>(patternToBeStored);

    auto elementToAdd =
            *(this->database.find(ifPatternToBeStored->getLineNumber())->second->getVariableNamesUsed().begin());

    this->database.find(ifPatternToBeStored->getLineNumber())->second->addAdditionalVariableOnLine(elementToAdd);
}

void IfPatternDatabase::addToDatabase(Pattern *patternToBeStored) {
    if (!(this->isValidPatternType(patternToBeStored))) {
        // Throw Error
        throw InvalidPatternTypeException(
                ("Got: " + patternToBeStored->getTypeOfPattern() + ". Expected: IfPattern Type Here").data());
    }

    IfPattern* ifPatternToBeStored = dynamic_cast<IfPattern*>(patternToBeStored);

    if (this->isLineNumberPresent(ifPatternToBeStored->getLineNumber())) {
        this->updatePatternInDatabase(patternToBeStored);
    } else {
        this->database.insert(make_pair(ifPatternToBeStored->getLineNumber(), ifPatternToBeStored));
    }
}

unordered_set<string> IfPatternDatabase::getAllVariablesBeingUsed(string lineNumber) {
    if (this->isLineNumberPresent(lineNumber)) {
        return this->database.find(lineNumber)->second->getVariableNamesUsed();
    }

    return unordered_set<string> {};
}

bool IfPatternDatabase::isVariableNamePresentOnLineNumber(string lineNumber, string variableName) {
    if (this->isLineNumberPresent(lineNumber)) {
        return this->database.find(lineNumber)->second->isVariableNamePresent(variableName);
    }

    return false;
}
