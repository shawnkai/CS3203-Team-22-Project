//
// Created by Jai Lulla  on 18/3/23.
//

#include <iostream>
#include <algorithm> // For Windows

#include "PatternDatabaseFactory.h"
#include "PKB/Pattern/IfPattern/IfPatternDatabaseFactory.h"
#include "PKB/Pattern/WhilePattern/WhilePatternDatabaseFactory.h"

#include "PKB/Exceptions/DatabaseNotFoundException.cpp"

using namespace std;

PatternDatabase *PatternDatabaseFactory::getIfPatternDatabase() {
    return IfPatternDatabaseFactory::getIfPatternDatabase();
}

PatternDatabase *PatternDatabaseFactory::getWhilePatternDatabase() {
    return WhilePatternDatabaseFactory::getWhilePatternDatabase();
}

PatternDatabase *PatternDatabaseFactory::getPatternDatabase(string patternType) {
    transform(patternType.begin(), patternType.end(), patternType.begin(), ::toupper);

    if (patternType == "IF") {
        return getIfPatternDatabase();
    } else if (patternType == "WHILE") {
        return getWhilePatternDatabase();
    }

    throw DatabaseNotFoundException(("Database for " + patternType + " could not be found").data());
}

void PatternDatabaseFactory::clearIfPatternFactory() {
    IfPatternDatabaseFactory::clearDatabase();
}

void PatternDatabaseFactory::clearWhilePatternFactory() {
    WhilePatternDatabaseFactory::clearDatabase();
}

void PatternDatabaseFactory::clearDatabase() {
    clearIfPatternFactory();
    clearWhilePatternFactory();
}
