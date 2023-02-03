#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"
#include "TNode.h"
#include "DesignEntities/DesignEntitiesFactory.h"
#include "DesignEntities/DesignEntitiesDatabase/DesignEntityDatabase.h"
#include "DesignEntities/DesignEntitiesDatabase/DesignEntitiesDatabaseFactory.h"

int PKB::setProcToAST(PROC p, TNode* r) {
	return 0;
}

TNode* PKB::getRootAST (PROC p){
	return nullptr;
}

void PKB::addDesignAbstraction(string designAbstraction, tuple<string, string> abstractionDetails) {
    // To be implemented
}

void PKB::addDesignEntity(string designEntity, tuple<string, string> entityDetails) {
    // To be implemented
    DesignEntity de = DesignEntitiesFactory::createDesignEntity(designEntity, entityDetails);
    de.addToDatabase();
}

Result PKB::getDesignAbstraction(string abstractionType, tuple<string, string> query) {
    // To be implemented

    // Demo Code
    vector<string> sampleVector(5, "");
    Result queryResult("sample", "sample", sampleVector);
    return queryResult;
}

Result PKB::getDesignEntity(string entityType, string entityName) {
    // To be implemented
    DesignEntityDatabase db = DesignEntitiesDatabaseFactory::getEntityDatabase(entityType);
    Result queryResult = db.getFromDatabase(entityName);

    return queryResult;
}

Result PKB::getDesignEntity(string entityType, string entityName, string occurrenceLine) {
    // To be implemented

    // Demo Code
    vector<string> sampleVector(5, "");
    Result queryResult("sample", "sample", sampleVector);
    return queryResult;
}