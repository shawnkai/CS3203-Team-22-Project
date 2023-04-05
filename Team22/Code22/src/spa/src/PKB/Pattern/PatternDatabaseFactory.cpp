//
// Created by Jai Lulla  on 18/3/23.
//

#include <iostream>
#include <algorithm> // For Windows

#include "PatternDatabaseFactory.h"

#include "PKB/Exceptions/DatabaseNotFoundException.cpp"

using namespace std;

PatternDatabase *PatternDatabaseFactory::getPatternDatabase(string patternType) {
    transform(patternType.begin(), patternType.end(), patternType.begin(), ::toupper);

    if (patternType == "IF") {
        return ifPatternDatabase;
    } else if (patternType == "WHILE") {
        return whilePatternDatabase;
    }

    throw DatabaseNotFoundException(("Database for " + patternType + " could not be found").data());
}

void PatternDatabaseFactory::clearIfPatternFactory() {
    delete ifPatternDatabase;

    ifPatternDatabase = new IfPatternDatabase();
}

void PatternDatabaseFactory::clearWhilePatternFactory() {
    delete whilePatternDatabase;

    whilePatternDatabase = new WhilePatternDatabase();
}

void PatternDatabaseFactory::clearDatabase() {
    clearIfPatternFactory();
    clearWhilePatternFactory();
}
