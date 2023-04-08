#ifndef SPA_PATTERNPREFIXSTRINGEXTRACTOR_H
#define SPA_PATTERNPREFIXSTRINGEXTRACTOR_H

#endif//SPA_PATTERNPREFIXSTRINGEXTRACTOR_H
#pragma once
#include <iostream>
#include <queue>
#include <stdio.h>
#include <string>
#include <tuple>
#include <vector>

#include "../../PKB/PKB.h"
#include "../Parser/TNode.h"

using namespace std;

class PatternPrefixStringExtractor {
public:
    PatternPrefixStringExtractor(){};
    void extractPrefixString(TNode root, PKB instance);

private:
    string handlePrefixGeneration(TNode node, string result);
};