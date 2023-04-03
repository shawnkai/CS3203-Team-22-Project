//
// Created by Jai Lulla  on 15/2/23.
//

#include <iostream>

#include "AssignPatternDatabase.h"

using namespace std;

/**
 * Returns true, if the given Left Hand Variable is present in the database, else false.
 *
 * @param assignPatternToBeStored The Left Hand Variable to be checked for is obtained from this pointer.
 * @return True, if the Left Hand Variable exists in the database.
 */
bool AssignPatternDatabase::isLeftHandVariablePresentInDatabase(AssignPattern *assignPatternToBeStored) {
    return this->isLeftHandVariablePresentInDatabase(assignPatternToBeStored->getLeftHandVariableName());
}

/**
 * Returns true, if the given Left Hand Variable is present in the database, else false.
 *
 * @param leftHandVariableName The Left Hand Variable to be checked for.
 * @return True, if the Left Hand Variable exists in the database.
 */
bool AssignPatternDatabase::isLeftHandVariablePresentInDatabase(string leftHandVariableName) {
    return !((this->database.find(leftHandVariableName)) == (this->database.end()));
}

/**
 * If the Variable already exists in the database, which is checked by logic, this
 * function can be called to push additional Right Hand Expressions related to the
 * existing Left Hand Variable that might be encountered at different lines in the program.
 *
 * @param assignPatternToBeStored The AssignPattern that already exists, from which details have to be extracted.
 */
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

/**
 * Adds the given Assign Pattern pointer to the database. If the Left Hand Variable in the
 * Assign Pattern pointer already exists, then it is updated in the database automatically,
 * without creating duplicate copies.
 *
 * @param assignPatternToBeStored The Assign Pattern pointer, that is to be stored or updated.
 */
void AssignPatternDatabase::addToDatabase(AssignPattern *assignPatternToBeStored) {
    if (this->isLeftHandVariablePresentInDatabase(assignPatternToBeStored)) {
        this->addRightHandExpressionForAnExistingVariableInDatabase(assignPatternToBeStored);
    } else {
        (this->database).insert(make_pair(assignPatternToBeStored->getLeftHandVariableName(), assignPatternToBeStored));
    }
}

/**
 * Returns the Right Hand Expression as a string, if the entered parameters are valid, and exist in the
 * database, else an empty string is returned.
 *
 * @param leftHandVariableName The Left Hand Variable to check for.
 * @param patternLineNumber The Line Number at which the Pattern occurs.
 * @return A string containing the Right Hand Expression or an empty string.
 */
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


/**
 * Returns an unordered_map that contains all the Right Hand Expressions of the given Left Hand Variable.
 * If the Left Hand Variable is invalid or does not exist, i.e., cannot be found in the database,
 * an empty unordered_map is returned.
 *
 * @param leftHandVariableName The Variable, whose Right Hand Expressions are to be obtained.
 * @return An unordered_map with all the Right Hand Expressions, if the Variable exists, else an Empty unordred_map is returned.
 */
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
 * This is useful for for wildcard type queries, where Left Hand
 * Variable parameter is a wildcard. An empty vector might be returned, if
 * the database is not populated.
 *
 * @return An unordered map consisting of all Assignment Patterns.
 */
unordered_map<string, unordered_map<string, string>> AssignPatternDatabase::getAllRightHandExpressionsFromDatabase() {
    unordered_map<string, unordered_map<string, string>> result;

    for (auto& [leftHandVariableName, assignPattern]: this->database) {
        result.insert(make_pair(leftHandVariableName, assignPattern->getAllRightHandExpressions()));
    }

    return result;
}
