#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <tuple>
#include <vector>

#include "../../PKB/PKB.h"
#include "ExtractorFactory.h"
#include "Extractor.h"
#include "SP/Parser/TNode.h"
#include "UtilityExtractor.h"

using namespace std;

extern std::map<string, vector<string>> mapOfWhileForCallStmts;
extern std::map<string, vector<string>> mapOfIfForCallStmts;
extern vector<string> callStmts;

class StmtlstExtractor : public Extractor {
public:
    TNode currentNode;
    std::vector<string> ifContainers;
    std::vector<string> whileContainers;
    std::string currentParent;
    std::string procedureName;
    PKB pkbinstance;

    StmtlstExtractor(TNode theNode, std::map<string, vector<string>> information, PKB pkbinstance1) {
        currentNode = theNode;
        ifContainers = information[ifContainerStr];
        whileContainers = information[whileContainerStr];
        vector<string> vector1 = information[containerLineNoStr];
        currentParent = vector1[0];
        vector<string> vector2 = information[procedureNameStr];
        procedureName = vector2[0];
        pkbinstance = pkbinstance1;
    }

    void extractAbstraction();

    //StmtlstExtractor(){};
    //void extractAbstraction(TNode root, std::vector<int> ifContainers, std::vector<int> whileContainers, PKB pkbinstance, int currentParent, std::string procedureName);
};