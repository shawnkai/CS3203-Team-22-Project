#pragma once

#include <iostream>
#include <queue>
#include <set>
#include <stdio.h>
#include <string>
#include <tuple>
#include <vector>

#include "../../PKB/PKB.h"
#include "Extractor.h"
#include "SP/Parser/TNode.h"

using namespace std;

class Extractor {
public:
    std::string procedureStr = "PROCEDURE";
    std::string followsStr = "FOLLOWS";
    std::string followsStarStr = "FOLLOWSSTAR";
    std::string parentStr = "PARENT";
    std::string parentStarStr = "PARENTSTAR";
    std::string callEntityStr = "CALLENTITY";
    std::string modifiesStr = "MODIFIES";
    std::string usesStr = "USES";
    std::string underlineStr = "_";
    std::string callsStr = "CALLS";
    std::string callStr = "CALL";
    std::string callsStarStr = "CALLSSTAR";
    std::string inverseCallsStr = "INVERSECALLS";

    std::string readStr = "READ";
    std::string printStr = "PRINT";
    std::string assignmentStr = "ASSIGNMENT";
    std::string statementStr = "STATEMENT";
    std::string procedurecallStr = "PROCEDURECALL";
    std::string ifStr = "IF";
    std::string whileStr = "WHILE";
    std::string variableStr = "VARIABLE";
    std::string constantStr = "CONSTANT";

    std::string ifContainerStr = "IfContainer";
    std::string whileContainerStr = "whileContainer";
    std::string procedureNameStr = "procedureName";
    std::string containerLineNoStr = "containerLineNo";

    Extractor(){};
    
    virtual void extractAbstraction() {}
    virtual void extractCallAbstraction(PKB pkbinstance) {}

    std::map<string, vector<string>> constructMap(std::vector<string> ifContainer, std::vector<string> whileContainer, std::string procedureName, std::string containerLineNo);
};