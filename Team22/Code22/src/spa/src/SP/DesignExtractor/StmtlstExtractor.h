#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include "../TNode.h"
#include "../../PKB/PKB.h"
#include "ReadPrintExtractor.h"
#include "WhileExtractor.h"
#include "IfExtractor.h"
#include "AssignExtractor.h"

using namespace std;

class StmtlstExtractor {
public:
	StmtlstExtractor() {};
	void extractAbstraction(TNode root);
};