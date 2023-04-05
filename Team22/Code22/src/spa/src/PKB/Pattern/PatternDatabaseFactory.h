//
// Created by Jai Lulla  on 18/3/23.
//

#pragma once

#ifndef SPA_PATTERNDATABASEFACTORY_H
#define SPA_PATTERNDATABASEFACTORY_H

#include <iostream>

#include "PatternDatabase.h"

using namespace std;

class PatternDatabaseFactory {
    static PatternDatabase* getIfPatternDatabase();
    static PatternDatabase* getWhilePatternDatabase();

    static void clearIfPatternFactory();
    static void clearWhilePatternFactory();

public:
    static PatternDatabase* getPatternDatabase(string patternType);

    static void clearDatabase();
};

#endif //SPA_PATTERNDATABASEFACTORY_H
