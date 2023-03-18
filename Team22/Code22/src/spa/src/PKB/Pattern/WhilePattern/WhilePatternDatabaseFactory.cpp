//
// Created by Jai Lulla  on 18/3/23.
//

#include <iostream>

#include "WhilePatternDatabaseFactory.h"

using namespace std;

PatternDatabase *WhilePatternDatabaseFactory::getWhilePatternDatabase() {
    return whilePatternDatabase;
}

void WhilePatternDatabaseFactory::clearDatabase() {
    delete whilePatternDatabase;

    whilePatternDatabase = new WhilePatternDatabase();
}
