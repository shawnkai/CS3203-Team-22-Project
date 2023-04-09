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
#include "ExtractorFactory.h"
#include "SP/Parser/TNode.h"
#include "Result.h"

using namespace std;


class ProgramExtractor : public Extractor {
public:

    TNode root;
    PKB pkbinstance;

    ProgramExtractor(TNode theNode, PKB pkbinstance1) {
        root = theNode;
        pkbinstance = pkbinstance1;
    };
    void extractAbstraction();
    void extractCallStarAbstractions(int noOfProcedures, std::vector<string> vectorOfProcedureNames, std::map<std::string, std::vector<string>> mapOfCalls, PKB pkbinstance);
    void extractCallAbstraction(PKB pkbinstance);
    vector<string> getAllCallStmts(vector<Result> callStmts1);
};

