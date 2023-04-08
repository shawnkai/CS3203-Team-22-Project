#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <tuple>
#include <vector>

#include "../../PKB/PKB.h"
#include "SP/Parser/TNode.h"
#include "StmtlstExtractor.h"

using namespace std;

class AbstractionExtractor {
public:
    AbstractionExtractor(){};
    void extractAbstraction(TNode root, PKB pkbinstance, std::string procedureName);
};