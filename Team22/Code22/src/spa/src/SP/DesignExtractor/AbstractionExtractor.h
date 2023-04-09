#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <tuple>
#include <vector>

#include "../../PKB/PKB.h"
#include "SP/Parser/TNode.h"
#include "ExtractorFactory.h"
#include "Extractor.h"

using namespace std;

class AbstractionExtractor : public Extractor {
public:
    TNode root;
    std::string procedureName;
    PKB pkbinstance;


    AbstractionExtractor(TNode theNode, std::map<string, vector<string>> information, PKB pkbinstance1) {
        root = theNode;
        vector<string> vector1 = information[procedureNameStr];
        procedureName = vector1[0];
        pkbinstance = pkbinstance1;
    };
    void extractAbstraction();
};