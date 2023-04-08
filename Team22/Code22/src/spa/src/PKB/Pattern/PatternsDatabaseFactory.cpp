//
// Created by Jai Lulla  on 18/3/23.
//

#include <algorithm>// For Windows
#include <iostream>

#include "PatternsDatabaseFactory.h"

#include "PKB/Exceptions/DatabaseNotFoundException.cpp"

using namespace std;

PatternDatabase *PatternsDatabaseFactory::getPatternDatabase(string patternType) {
    transform(patternType.begin(), patternType.end(), patternType.begin(), ::toupper);

    if (patternType == "IF") {
        return ifPatternDatabase;
    } else if (patternType == "WHILE") {
        return whilePatternDatabase;
    }

    throw DatabaseNotFoundException(("Database for " + patternType + " could not be found").data());
}

void PatternsDatabaseFactory::clearIfPatternFactory() {
    delete ifPatternDatabase;

    ifPatternDatabase = new IfPatternDatabase();
}

void PatternsDatabaseFactory::clearWhilePatternFactory() {
    delete whilePatternDatabase;

    whilePatternDatabase = new WhilePatternDatabase();
}

void PatternsDatabaseFactory::clearDatabase() {
    clearIfPatternFactory();
    clearWhilePatternFactory();
}
