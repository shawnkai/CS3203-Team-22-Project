//
// Created by Jai Lulla  on 30/3/23.
//

#include <iostream>

#include "PKB/Pattern/AssignPattern/AssignPatternFactory.h"
#include "PKB/Pattern/AssignPattern/AssignPatternDatabaseFactory.h"
#include "PKB/Pattern//PatternFactory.h"
#include "PKB/Pattern/PatternDatabaseFactory.h"

#include "PatternsController.h"

using namespace std;

/**
 * This method allows to add an Assignment Pattern to the Program Knowledge Base.
 *
 * @param leftHandVariableName The name of the variable that is being assigned to.
 * @param prefixExpression The expression on the right hand side, which has been converted into its prefix form.
 * @param patternLineNumber The line number at which this assignment pattern can be observed.
 */
void PatternsController::addAssignPattern(string leftHandVariableName, string prefixExpression, string patternLineNumber) {
    AssignPattern* assignPattern = AssignPatternFactory::createAssignPattern(leftHandVariableName, prefixExpression,
                                                                             patternLineNumber);
    assignPattern->addToDatabase();
}

/**
 * Returns a string containing the Right Hand Prefix Expression, for the given left hand variable name
 * and line number, else returns an empty string, if any pattern stored for the given combinations
 * cannot be found.
 *
 * @param leftHandVariableName The variable, which has been assigned, to be looked for.
 * @param patternLineNumber The line number at which this assignment took place.
 * @return A string containing the Right Hand Prefix Expression or an empty string.
 */
string
PatternsController::getRightHandExpressionOfAVariableOnAParticularLineNumber(string leftHandVariableName, string patternLineNumber) {
    AssignPatternDatabase* assignPatternDatabase = AssignPatternDatabaseFactory::getAssignPatternDatabase();
    return assignPatternDatabase
            ->getRightHandExpressionOfAVariableOnAParticularLineNumberFromDatabase(leftHandVariableName, patternLineNumber);
}

/**
 * Returns an unordered map containing all the Right Hand Prefix Expression associated to a given
 * variable, that would have occurred on the left hand side.
 *
 * @param leftHandVariableName The variable, which has been assigned, to be looked for.
 * @return An unordered map containing all the Right Hand Prefix Expressions associated to the given variable.
 */
unordered_map<string, string> PatternsController::getAllRightHandExpressionsOfAVariable(string leftHandVariableName) {
    AssignPatternDatabase* assignPatternDatabase = AssignPatternDatabaseFactory::getAssignPatternDatabase();
    return assignPatternDatabase->getAllRightHandExpressionsOfAVariableFromDatabase(leftHandVariableName);
}

/**
 * Returns a vector of AssignPattern pointer objects, that contain all the patterns derivable from
 * the assignment statements. This is particularly useful, when wildcards come into play.
 *
 * @return A vector of AssignPattern pointer objects, or an empty vector, if nothing is stored.
 */
unordered_map<string, unordered_map<string, string>> PatternsController::getAllRightHandExpressions() {
    AssignPatternDatabase* assignPatternDatabase = AssignPatternDatabaseFactory::getAssignPatternDatabase();
    return assignPatternDatabase->getAllRightHandExpressionsFromDatabase();
}

void PatternsController::addPattern(string patternType, string lineNumber, string variableName) {
    Pattern* patternToBeStored = PatternFactory::createPattern(patternType, lineNumber, variableName);
    PatternDatabase* db = PatternDatabaseFactory::getPatternDatabase(patternType);

    db->addToDatabase(patternToBeStored);
}

bool PatternsController::isVariableUsedInPattern(string patternType, string lineNumber, string variableName) {
    PatternDatabase* db = PatternDatabaseFactory::getPatternDatabase(patternType);

    return db->isVariableNamePresentOnLineNumber(lineNumber, variableName);
}

unordered_set<string> PatternsController::getAllVariablesUsedInPattern(string patternType, string lineNumber) {
    PatternDatabase* db = PatternDatabaseFactory::getPatternDatabase(patternType);

    return db->getAllVariablesBeingUsed(lineNumber);
}
