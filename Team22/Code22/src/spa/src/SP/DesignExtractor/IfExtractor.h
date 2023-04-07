#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <tuple>
#include <vector>

#include "../../PKB/PKB.h"
#include "ReadPrintExtractor.h"
#include "SP/Parser/TNode.h"
#include "WhileExtractor.h"

using namespace std;

class IfExtractor {
public:
    IfExtractor(){};
    void extractAbstraction(TNode root, std::vector<int> ifContainers, std::vector<int> whileContainers, PKB pkbinstance, std::string procedureName);
};