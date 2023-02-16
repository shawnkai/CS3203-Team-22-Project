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

using namespace std;

class IfExtractor {
public:
	IfExtractor() {};
	void extractAbstraction(TNode root);
};