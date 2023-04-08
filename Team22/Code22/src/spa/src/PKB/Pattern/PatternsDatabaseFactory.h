//
// Created by Jai Lulla  on 18/3/23.
//

#pragma once

#ifndef SPA_PATTERNSDATABASEFACTORY_H
#define SPA_PATTERNSDATABASEFACTORY_H

#include <iostream>

#include "PKB/Pattern/IfPattern/IfPatternDatabase.h"
#include "PKB/Pattern/WhilePattern/WhilePatternDatabase.h"
#include "PatternDatabase.h"

using namespace std;

class PatternsDatabaseFactory {
    static inline PatternDatabase *ifPatternDatabase = new IfPatternDatabase();
    static inline PatternDatabase *whilePatternDatabase = new WhilePatternDatabase();

    static void clearIfPatternFactory();
    static void clearWhilePatternFactory();

public:
    static PatternDatabase *getPatternDatabase(string patternType);

    static void clearDatabase();
};

#endif//SPA_PATTERNSDATABASEFACTORY_H
