#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <deque>
#include <queue>
#include <unordered_set>

#include "../../PKB/PKB.h"
#include "SP/Parser/TNode.h"

using namespace std;

class NextExtractor {
public:
	NextExtractor() {};
	void extractAbstraction(vector<int> orderedBlks, std::unordered_map<int, vector<int>> blkToStmtMap, std::unordered_map<int, int> stmtToBlkMap, std::unordered_map<int, vector<int>> blkToBlkMap, std::unordered_set<int> setOfWhile, PKB pkbinstance, std::string procedureName);
	vector<deque<int>> findPath(vector<int> orderedBlks, std::unordered_map<int, vector<int>> blkToBlkMap, std::unordered_set<int> setOfWhile, int nextBlk, int currBlk);
	vector<deque<int>> findWhileStmtlstPath(vector<int> orderedBlks, std::unordered_map<int, vector<int>> blkToBlkMap, std::unordered_set<int> setOfWhile, int nextBlk, int currBlk, int exitWhile);
	vector<deque<int>> findWhilePath(vector<int> orderedBlks, std::unordered_map<int, vector<int>> blkToBlkMap, std::unordered_set<int> setOfWhile, int currBlk, int whileBlk);
	void addWithinBlkNextAbstraction(int blkNo, std::unordered_map<int, vector<int>> blkToStmtMap, PKB pkbinstance);
	void addBtwBlkNextAbstraction(int prevBlk, int nextBlk, std::unordered_map<int, vector<int>> blkToStmtMap, PKB pkbinstance);
};