#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <tuple>
#include <vector>

#include "../../PKB/PKB.h"
#include "Result.h"
#include "SP/Parser/TNode.h"
#include "ExtractorFactory.h"
#include "Extractor.h"
#include "RelationshipExtractor.h"

using namespace std;

class ReadPrintExtractor : public Extractor {
public:
    TNode currentNode;
    std::vector<string> ifContainers;
    std::vector<string> whileContainers;
    std::string procedureName;
    PKB pkbinstance;

    ReadPrintExtractor(TNode theNode, std::map<string, vector<string>> information, PKB pkbinstance1) {
        currentNode = theNode;
        ifContainers = information[ifContainerStr];
        whileContainers = information[whileContainerStr];
        vector<string> vector1 = information[procedureNameStr];
        procedureName = vector1[0];
        pkbinstance = pkbinstance1;
    }

    void extractAbstraction();

};