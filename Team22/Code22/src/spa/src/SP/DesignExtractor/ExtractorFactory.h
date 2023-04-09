#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <tuple>
#include <vector>

#include "../../PKB/PKB.h"
#include "AbstractionExtractor.h"
#include "AssignExtractor.h"
#include "ConditionExtractor.h"
#include "Extractor.h"
#include "IfExtractor.h"
#include "ProgramExtractor.h"
#include "SP/Parser/TNode.h"
#include "StmtlstExtractor.h"
#include "WhileExtractor.h"

using namespace std;

class ExtractorFactory {
public:
    std::shared_ptr<Extractor> createExtractor(TNode currentNode, std::map<string, vector<string>> information, PKB pkbinstance);
};
