#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"
#include "TNode.h"

int PKB::setProcToAST(PROC p, TNode* r) {
	return 0;
}

TNode* PKB::getRootAST (PROC p){
	return nullptr;
}

void PKB::addDesignAbstraction(string designAbstraction, tuple<string, string> abstractionDetails) {

}

void PKB::addDesignEntity(string designEntity, string occurrenceLine) {

}

Result PKB::getDesignAbstraction(string abstractionType, tuple<string, string> query) {
    vector<string> sampleVector(5, "");
    Result queryResult(sampleVector);
    return queryResult;
}

Result PKB::getDesignEntity(string entityType) {
    vector<string> sampleVector(5, "");
    Result queryResult(sampleVector);
    return queryResult;
}

Result PKB::getDesignEntity(string entityType, string occurrenceLine) {
    vector<string> sampleVector(5, "");
    Result queryResult(sampleVector);
    return queryResult;
}