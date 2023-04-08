#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <tuple>
#include <vector>

#include "../../PKB/PKB.h"
#include "ConditionExtractor.h"
#include "SP/Parser/TNode.h"
#include "StmtlstExtractor.h"

using namespace std;

class WhileExtractor {
public:
    WhileExtractor(){};
    void extractAbstraction(TNode root, std::vector<int> ifContainers, std::vector<int> whileContainers, PKB pkbinstance, std::string procedureName);
};