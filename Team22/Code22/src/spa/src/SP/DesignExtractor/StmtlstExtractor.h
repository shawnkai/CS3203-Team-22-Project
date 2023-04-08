#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <tuple>
#include <vector>

#include "../../PKB/PKB.h"
#include "AssignExtractor.h"
#include "IfExtractor.h"
#include "ReadPrintExtractor.h"
#include "SP/Parser/TNode.h"
#include "WhileExtractor.h"

using namespace std;

extern std::map<int, vector<int>> mapOfWhileForCallStmts;
extern std::map<int, vector<int>> mapOfIfForCallStmts;
extern vector<int> callStmts;

class StmtlstExtractor {
public:
    StmtlstExtractor(){};
    void extractAbstraction(TNode root, std::vector<int> ifContainers, std::vector<int> whileContainers, PKB pkbinstance, int currentParent, std::string procedureName);
};