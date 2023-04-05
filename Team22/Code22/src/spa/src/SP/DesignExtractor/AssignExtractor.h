#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <map>

#include "SP/Parser/TNode.h"
#include "../../PKB/PKB.h"
#include "PatternPrefixStringExtractor.h"

using namespace std;

extern std::map<string, vector<string>> mapOfModifiedVarforCalls;
extern std::map<string, vector<string>> mapOfUsedVarforCalls;

class AssignExtractor {
public:
	AssignExtractor() {};
	void extractAbstraction(TNode currentNode, std::vector<int> ifContainers, std::vector<int> whileContainers, PKB pkbinstance, std::string procedureName);
};