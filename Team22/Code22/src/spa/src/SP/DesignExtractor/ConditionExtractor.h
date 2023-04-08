#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <tuple>
#include <vector>

#include "../../PKB/PKB.h"
#include "SP/Parser/TNode.h"

using namespace std;

extern std::map<string, vector<string>> mapOfUsedVarforCalls;

class ConditionExtractor {
public:
    ConditionExtractor(){};
    void extractAbstraction(TNode currentNode, std::vector<int> ifContainers, std::vector<int> whileContainers, PKB pkbinstance, std::string procedureName, TNode prevNode);
};