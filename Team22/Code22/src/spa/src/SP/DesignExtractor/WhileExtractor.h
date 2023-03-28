#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include "SP/Parser/TNode.h"
#include "../../PKB/PKB.h"
#include "StmtlstExtractor.h"
#include "ConditionExtractor.h"

using namespace std;

class WhileExtractor {
public:
	WhileExtractor() {};
	void extractAbstraction(TNode root, std::vector<int> ifContainers, std::vector<int> whileContainers, PKB pkbinstance, std::string procedureName);
};