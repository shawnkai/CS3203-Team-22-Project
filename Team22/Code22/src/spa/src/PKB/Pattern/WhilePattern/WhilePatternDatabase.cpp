//
// Created by Jai Lulla  on 18/3/23.
//

#include <iostream>

#include "WhilePatternDatabase.h"

#include "PKB/Exceptions/InvalidPatternTypeException.cpp"

using namespace std;

bool WhilePatternDatabase::isValidPatternType(Pattern *patternToBeStored) {
    WhilePattern* whilePatternToBeStored = dynamic_cast<WhilePattern*>(patternToBeStored);

    if (whilePatternToBeStored == nullptr) {
        return false;
    }

    return true;
}

bool WhilePatternDatabase::isLineNumberPresent(string lineNumber) {
    return (this->database.find(lineNumber) != this->database.end());
}

void WhilePatternDatabase::updatePatternInDatabase(Pattern *patternToBeStored) {
    if (!(this->isValidPatternType(patternToBeStored))) {
        // Throw Error
        throw InvalidPatternTypeException(
                ("Got: " + patternToBeStored->getTypeOfPattern() + ". Expected: WhilePattern Type Here").data());
    }

    WhilePattern* whilePatternToBeStored = dynamic_cast<WhilePattern*>(patternToBeStored);

    auto elementToAdd =
            *(this->database.find(whilePatternToBeStored->getLineNumber())->second->getVariableNamesUsed().begin());

    this->database.find(whilePatternToBeStored->getLineNumber())->second->addAdditionalVariableOnLine(elementToAdd);
}

void WhilePatternDatabase::addToDatabase(Pattern *patternToBeStored) {
    if (!(this->isValidPatternType(patternToBeStored))) {
        // Throw Error
        throw InvalidPatternTypeException(
                ("Got: " + patternToBeStored->getTypeOfPattern() + ". Expected: WhilePattern Type Here").data());
    }

    WhilePattern* whilePatternToBeStored = dynamic_cast<WhilePattern*>(patternToBeStored);

    if (this->isLineNumberPresent(whilePatternToBeStored->getLineNumber())) {
        this->updatePatternInDatabase(patternToBeStored);
    } else {
        this->database.insert(make_pair(whilePatternToBeStored->getLineNumber(), whilePatternToBeStored));
    }
}

unordered_set<string> WhilePatternDatabase::getAllVariablesBeingUsed(string lineNumber) {
    if (this->isLineNumberPresent(lineNumber)) {
        return this->database.find(lineNumber)->second->getVariableNamesUsed();
    }

    return unordered_set<string> {};
}

bool WhilePatternDatabase::isVariableNamePresentOnLineNumber(string lineNumber, string variableName) {
    if (this->isLineNumberPresent(lineNumber)) {
        return this->database.find(lineNumber)->second->isVariableNamePresent(variableName);
    }

    return false;
}
