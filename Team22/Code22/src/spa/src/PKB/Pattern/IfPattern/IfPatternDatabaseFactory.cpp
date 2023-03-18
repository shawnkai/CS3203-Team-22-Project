//
// Created by Jai Lulla  on 18/3/23.
//

#include <iostream>

#include "IfPatternDatabaseFactory.h"

using namespace std;

PatternDatabase *IfPatternDatabaseFactory::getIfPatternDatabase() {
    return ifPatternDatabase;
}

void IfPatternDatabaseFactory::clearDatabase() {
    delete ifPatternDatabase;

    ifPatternDatabase = new IfPatternDatabase();
}
