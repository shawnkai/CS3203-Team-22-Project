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
    std::string procedureStr = "PROCEDURE";
    std::string procedurecallStr = "PROCEDURECALL";
    std::string statementStr = "STATEMENT";
    std::string ifStr = "IF";
    std::string whileStr = "WHILE";

    RelationshipExtractor(){};
    void extractModifiesorUsesAbstraction(string type1, PKB pkbinstance, string procedureName, string variableName, int lineNumOfVariable);
    void extractContainerUsesOrModifiesAbstraction(string type1, vector<string> ifContainers, vector<string> whileContainers, PKB pkbinstance, string variableName);
};