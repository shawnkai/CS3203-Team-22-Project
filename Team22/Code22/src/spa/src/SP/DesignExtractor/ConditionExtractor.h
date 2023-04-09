#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <tuple>
#include <vector>

#include "../../PKB/PKB.h"
#include "SP/Parser/TNode.h"

using namespace std;

class ConditionExtractor {
public:
    ConditionExtractor(){};
    void extractConditionAbstraction(TNode currentNode, std::vector<string> ifContainers, std::vector<string> whileContainers, PKB pkbinstance, std::string procedureName, TNode prevNode);
};