#ifndef SPA_PATTERNPREFIXSTRINGEXTRACTOR_H
#define SPA_PATTERNPREFIXSTRINGEXTRACTOR_H

#endif //SPA_PATTERNPREFIXSTRINGEXTRACTOR_H
#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>

#include "../Parser/TNode.h"
#include "../../PKB/PKB.h"

using namespace std;

class PatternPrefixStringExtractor {
public:
    PatternPrefixStringExtractor() {};
    void extractPrefixString(TNode root, PKB instance);
private:
    string handlePrefixGeneration(TNode node, string result);
};