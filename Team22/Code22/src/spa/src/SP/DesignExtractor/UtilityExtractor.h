#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <tuple>
#include <vector>

#include "../../PKB/PKB.h"
#include "SP/Parser/TNode.h"

using namespace std;

class UtilityExtractor {
private:
    static std::map<string, vector<string>> mapOfWhileForCallStmts;
    static std::map<string, vector<string>> mapOfIfForCallStmts;
    static std::map<string, vector<string>> mapOfModifiedVarforCalls;
    static std::map<string, vector<string>> mapOfUsedVarforCalls;
    static vector<string> callStmts;

public:
    UtilityExtractor(){};
    std::map<string, vector<string>> getmapOfWhileForCallStmts();
    std::map<string, vector<string>> getmapOfIfForCallStmts();
    std::map<string, vector<string>> getmapOfModifiedVarforCalls();
    std::map<string, vector<string>> getmapOfUsedVarforCalls(); 
    vector<string> UtilityExtractor::getcallStmts();
    void setmapOfWhileForCallStmts(std::map<string, vector<string>> mapOfWhileForCallStmts1);
    void setmapOfIfForCallStmts(std::map<string, vector<string>> mapOfIfForCallStmts1);
    void setmapOfModifiedVarforCalls(std::map<string, vector<string>> mapOfModifiedVarforCalls1);
    void setmapOfUsedVarforCalls(std::map<string, vector<string>> mapOfUsedVarforCalls1);
    void setCallStmts(vector<string> callStmts1);
};