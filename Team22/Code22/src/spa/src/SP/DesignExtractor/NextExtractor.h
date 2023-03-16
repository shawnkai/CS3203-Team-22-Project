#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <unordered_set>

#include "../../PKB/PKB.h"
#include "SP/Parser/TNode.h"

using namespace std;

class NextExtractor {
public:
	NextExtractor() {};
	void extractAbstraction(vector<int> orderedBlks, std::map<int, vector<int>> blkToStmtMap, std::map<int, int> stmtToBlkMap, std::map<int, vector<int>> blkToBlkMap, std::unordered_set<int> setOfWhile);
};