#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <utility>


using namespace std;

#include "UtilityExtractor.h"

std::map<string, vector<string>> UtilityExtractor::mapOfWhileForCallStmts;
std::map<string, vector<string>> UtilityExtractor::mapOfIfForCallStmts;
std::map<string, vector<string>> UtilityExtractor::mapOfModifiedVarforCalls;
std::map<string, vector<string>> UtilityExtractor::mapOfUsedVarforCalls;
vector<string> UtilityExtractor::callStmts;

std::map<string, vector<string>> UtilityExtractor::getmapOfWhileForCallStmts() {
    return UtilityExtractor::mapOfWhileForCallStmts;
}

std::map<string, vector<string>> UtilityExtractor::getmapOfIfForCallStmts() {
    return UtilityExtractor::mapOfIfForCallStmts;
}

std::map<string, vector<string>> UtilityExtractor::getmapOfModifiedVarforCalls() {
    return UtilityExtractor::mapOfModifiedVarforCalls;
}

std::map<string, vector<string>> UtilityExtractor::getmapOfUsedVarforCalls() {
    return UtilityExtractor::mapOfUsedVarforCalls;
}

vector<string> UtilityExtractor::getcallStmts() {
    return UtilityExtractor::callStmts;
}

void UtilityExtractor::setmapOfWhileForCallStmts(std::map<string, vector<string>> mapOfWhileForCallStmts1) {
    UtilityExtractor::mapOfWhileForCallStmts = mapOfWhileForCallStmts1;
}

void UtilityExtractor::setmapOfIfForCallStmts(std::map<string, vector<string>> mapOfIfForCallStmts1) {
    UtilityExtractor::mapOfIfForCallStmts = mapOfIfForCallStmts1;
}

void UtilityExtractor::setmapOfModifiedVarforCalls(std::map<string, vector<string>> mapOfModifiedVarforCalls1) {
    UtilityExtractor::mapOfModifiedVarforCalls = mapOfModifiedVarforCalls1;
}

void UtilityExtractor::setmapOfUsedVarforCalls(std::map<string, vector<string>> mapOfUsedVarforCalls1) {
    UtilityExtractor::mapOfUsedVarforCalls = mapOfUsedVarforCalls1;
}

void UtilityExtractor::setCallStmts(vector<string> callStmts1) {
    UtilityExtractor::callStmts = callStmts1;
}