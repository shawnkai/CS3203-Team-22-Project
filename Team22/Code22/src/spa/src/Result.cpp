//
// Created by Jai Lulla  on 2/2/23.
//

#include <iostream>

#include "Result.h"

using namespace std;

/**
 * Creates a Result object, with the given parameters. This can be overloaded
 * for storing Design Entities and Design Abstractions.
 *
 * @param entityType The type of the Design Entity or Design Abstraction.
 * @param entityName The name of the Design Entity synonym, or Design Abstraction.
 * @param result A vector of string, containing the result of occurrences.
 */
Result::Result(string entityType, string entityName, vector<string> result) {
    this->entityType = entityType;
    this->entityName = entityName;
    this->result = result;
}

/**
 * Returns the details encapsulated by the Result, in a string format.
 *
 * @return A string with the details of the Result object.
 */
string Result::toString() const {
    string resultString = (this->entityType) + ": " + (this->entityName) + ": ";

    for (auto item: this->result) {
        resultString += (item + ", ");
    }

    return resultString;
}

/**
 * Returns the name of the Design Entity or Design Abstraction,
 * whose result is stored.
 *
 * @return A string with name of the Design Entity or Design Abstraction.
 */
string Result::getQueryEntityName() {
    return this->entityName;
}

/**
 * Returns the type of the Design Entity or Design Abstraction.
 *
 * @return A string, describing the type of Design Entity or Design Abstraction.
 */
string Result::getQueryEntityType() {
    return this->entityType;
}

/**
 * Returns a vector of strings, containing the result,
 * that had been stored in the Result.
 *
 * @return A vector of strings, containing occurrences.
 */
vector<string> Result::getQueryResult() {
    return this->result;
}

/**
 * Returns true, if both the Result objects being compared are the same, else
 * returns false.
 *
 * @param otherResult The Result object to be compared against.
 * @return A boolean, true, if both the Result objects match, false otherwise.
 */
bool Result::areEqual(Result otherResult) {
    return (this->entityName == otherResult.entityName)
    && (this->entityType == otherResult.entityType)
    && (this->result == otherResult.result);
}
