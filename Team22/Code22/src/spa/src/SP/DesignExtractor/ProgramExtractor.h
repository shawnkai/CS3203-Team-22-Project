#pragma once

#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stdio.h>
#include <string>
#include <tuple>
#include <vector>

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
    ProgramExtractor(){};
    void extractAbstraction(TNode root, PKB pkbinstance);
    void extractCallAbstraction(PKB pkbinstance);
};