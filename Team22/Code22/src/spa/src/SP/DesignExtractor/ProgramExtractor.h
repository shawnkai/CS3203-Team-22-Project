#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <set>
#include <queue>

#include "../../PKB/PKB.h"
#include "AbstractionExtractor.h"
#include "SP/Parser/TNode.h"

using namespace std;

class ProgramExtractor {
public:
	ProgramExtractor() {};
	void extractAbstraction(TNode root, PKB pkbinstance);
};