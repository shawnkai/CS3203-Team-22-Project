//
// Created by Jai Lulla  on 18/3/23.
//

#pragma once

#ifndef SPA_WHILEPATTERNDATABASEFACTORY_H
#define SPA_WHILEPATTERNDATABASEFACTORY_H

#include <iostream>

#include "WhilePatternDatabase.h"

using namespace std;

class WhilePatternDatabaseFactory {
    static inline PatternDatabase* whilePatternDatabase = new WhilePatternDatabase();

public:
    static PatternDatabase* getWhilePatternDatabase();

    static void clearDatabase();
};

#endif //SPA_WHILEPATTERNDATABASEFACTORY_H
