#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include "SP/Parser/TNode.h"
#include "../../PKB/PKB.h"
#include "PatternPrefixStringExtractor.h"

using namespace std;

class AssignExtractor {
public:
	AssignExtractor() {};
	void extractAbstraction(TNode currentNode, std::vector<int> ifContainers, std::vector<int> whileContainers, PKB pkbinstance, std::string procedureName);
};