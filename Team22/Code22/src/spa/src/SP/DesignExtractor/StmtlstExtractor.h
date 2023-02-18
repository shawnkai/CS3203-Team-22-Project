#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include "SP/Parser/TNode.h"
#include "../../PKB/PKB.h"
#include "ReadPrintExtractor.h"
#include "WhileExtractor.h"
#include "IfExtractor.h"
#include "AssignExtractor.h"

using namespace std;

class StmtlstExtractor {
public:
	StmtlstExtractor() {};
	void extractAbstraction(TNode root, std::vector<int> ifContainers, std::vector<int> whileContainers, PKB pkbinstance, int currentParent);
};