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

extern std::map<int, vector<int>> mapOfWhileForCallStmts;
extern std::map<int, vector<int>> mapOfIfForCallStmts;
extern std::map<string, vector<string>> mapOfModifiedVarforCalls;
extern std::map<string, vector<string>> mapOfUsedVarforCalls;
extern vector<int> callStmts;

class ProgramExtractor {
public:
	ProgramExtractor() {};
	void extractAbstraction(TNode root, PKB pkbinstance);
	void extractCallAbstraction(PKB pkbinstance);
};