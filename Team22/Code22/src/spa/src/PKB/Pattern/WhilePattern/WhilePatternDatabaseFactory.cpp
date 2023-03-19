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
    // Warning Generated
    //    delete whilePatternDatabase;

    whilePatternDatabase = new WhilePatternDatabase();
}
