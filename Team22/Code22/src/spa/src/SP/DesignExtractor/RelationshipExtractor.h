#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <tuple>
#include <vector>

#include "../../PKB/PKB.h"
#include "SP/Parser/TNode.h"

using namespace std;

class RelationshipExtractor {
public:
    RelationshipExtractor(){};
    void extractRelationshipAbstraction(TNode root, PKB pkbinstance, std::string procedureName);
};