#pragma once

#include <deque>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../../PKB/PKB.h"
#include "SP/Parser/TNode.h"

using namespace std;

class NextExtractor {
public:
    NextExtractor(){};
    void extractAbstraction(vector<int> orderedBlks, std::unordered_map<int, vector<int>> blkToStmtMap, std::unordered_map<int, int> stmtToBlkMap, std::unordered_map<int, vector<int>> blkToBlkMap, std::unordered_set<int> setOfWhile, PKB pkbinstance, std::string procedureName);
    void addWithinBlkNextAbstraction(int blkNo, std::unordered_map<int, vector<int>> blkToStmtMap, PKB pkbinstance);
    void addBtwBlkNextAbstraction(int prevBlk, int nextBlk, std::unordered_map<int, vector<int>> blkToStmtMap, PKB pkbinstance);
};