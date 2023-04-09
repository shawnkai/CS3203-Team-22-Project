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