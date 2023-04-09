#include <iostream>
#include <stdio.h>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

#include "../../PKB/PKB.h"
#include "Extractor.h"

std::map<string, vector<string>> Extractor::constructMap(std::vector<string> ifContainer, std::vector<string> whileContainer, std::string procedureName, std::string containerLineNo) {
    std::map<string, vector<string>> newmap;
    newmap[ifContainerStr] = ifContainer;
    newmap[whileContainerStr] = whileContainer;
    vector<string> vector1;
    vector1.push_back(procedureName);
    newmap[procedureNameStr] = vector1;
    vector<string> vector3;
    vector3.push_back(containerLineNo);
    newmap[containerLineNoStr] = vector3;
    return newmap;
};

std::map<string, vector<string>> Extractor::mapOfWhileForCallStmts;
std::map<string, vector<string>> Extractor::mapOfIfForCallStmts;

std::map<string, vector<string>> Extractor::getmapOfWhileForCallStmts() {
    return Extractor::mapOfWhileForCallStmts;
}

std::map<string, vector<string>> Extractor::getmapOfIfForCallStmts() {
    return Extractor::mapOfIfForCallStmts;
}

void Extractor::setmapOfWhileForCallStmts(std::map<string, vector<string>> mapOfWhileForCallStmts1) {
    Extractor::mapOfWhileForCallStmts = mapOfWhileForCallStmts1;
}

void Extractor::setmapOfIfForCallStmts(std::map<string, vector<string>> mapOfIfForCallStmts1) {
    Extractor::mapOfIfForCallStmts = mapOfIfForCallStmts1;
}