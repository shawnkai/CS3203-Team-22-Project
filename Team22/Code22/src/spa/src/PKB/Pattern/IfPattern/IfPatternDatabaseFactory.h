//
// Created by Jai Lulla  on 18/3/23.
//

#pragma once

#ifndef SPA_IFPATTERNDATABASEFACTORY_H
#define SPA_IFPATTERNDATABASEFACTORY_H

#include <iostream>

#include "IfPatternDatabase.h"

using namespace std;

class IfPatternDatabaseFactory {
    static inline PatternDatabase* ifPatternDatabase = new IfPatternDatabase();

public:
    static PatternDatabase* getIfPatternDatabase();

    static void clearDatabase();
};

#endif //SPA_IFPATTERNDATABASEFACTORY_H
