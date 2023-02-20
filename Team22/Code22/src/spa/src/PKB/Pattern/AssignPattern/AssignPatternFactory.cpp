//
// Created by Jai Lulla  on 16/2/23.
//

#include <iostream>

#include "AssignPatternFactory.h"

using namespace std;

/**
 * Returns a newly created AssignPattern pointer, using the passed in parameters.
 *
 * @param leftHandVariableName The variable on the left hand side of the expression.
 * @param prefixExpression The prefix version of the expression on the right hand side.
 * @param patternLineNumber The line number at which this assignment pattern occurs.
 * @return An AssignPattern pointer, with all the details being captured in it.
 */
AssignPattern *AssignPatternFactory::createAssignPattern(string leftHandVariableName, string prefixExpression,
                                                         string patternLineNumber) {
    return new AssignPattern(leftHandVariableName, prefixExpression, patternLineNumber);
}
