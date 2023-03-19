//
// Created by Jai Lulla  on 18/3/23.
//

#include <iostream>
#include <algorithm> // For Windows

#include "PatternFactory.h"
#include "PKB/Pattern/IfPattern/IfPatternFactory.h"
#include "PKB/Pattern/WhilePattern/WhilePatternFactory.h"

#include "PKB/Exceptions/InvalidPatternTypeException.cpp"

using namespace std;

Pattern *PatternFactory::createPattern(string patternType, string lineNumber, string variableName) {
    transform(patternType.begin(), patternType.end(), patternType.begin(), ::toupper);

    if (patternType == "IF") {
        return IfPatternFactory::createIfPattern(lineNumber, variableName);
    } else if (patternType == "WHILE") {
        return WhilePatternFactory::createWhilePattern(lineNumber, variableName);
    }

    throw InvalidPatternTypeException((patternType + " is not a valid Pattern Type").data());
}
