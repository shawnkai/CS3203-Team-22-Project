#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"
#include "TNode.h"

#include "DesignAbstractions/DesignAbstractionsFactory.h"
#include "DesignAbstractions/DesignAbstractionsDatabase/DesignAbstractionDatabase.h"
#include "DesignAbstractions/DesignAbstractionsDatabase/DesignAbstractionsDatabaseFactory.h"

#include "DesignEntities/DesignEntitiesFactory.h"
#include "DesignEntities/DesignEntitiesDatabase/DesignEntityDatabase.h"
#include "DesignEntities/DesignEntitiesDatabase/DesignEntitiesDatabaseFactory.h"

void PKB::addDesignAbstraction(string designAbstraction, tuple<string, string, string> abstractionDetails) {
    // To be implemented -> Done [05/02/2023]
    DesignAbstraction* da = DesignAbstractionsFactory::createDesignAbstraction(designAbstraction, abstractionDetails);
    da->addToDatabase();
}

void PKB::addDesignEntity(string designEntity, tuple<string, string> entityDetails) {
    // To be implemented -> Done [05/02/2023]
    DesignEntity* de = DesignEntitiesFactory::createDesignEntity(designEntity, entityDetails);
    de->addToDatabase();
}

Result PKB::getDesignAbstraction(string abstractionType, tuple<string, string> query) {
    // To be implemented -> Done [05/02/2023]
    DesignAbstractionDatabase* db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase(abstractionType,
                                                                                              get<0>(query));
    Result queryResult = db->getFromDatabase(get<1>(query));

    return queryResult;
}

Result PKB::getDesignEntity(string entityType, string entityName) {
    // To be implemented -> Done [05/02/2023]
    DesignEntityDatabase* db = DesignEntitiesDatabaseFactory::getEntityDatabase(entityType);
    Result queryResult = db->getFromDatabase(entityName);

    return queryResult;
}

Result PKB::getDesignEntity(string entityType, string entityName, string occurrenceLine) {
    // To be implemented

    // Demo Code
    vector<string> sampleVector(5, "");
    Result queryResult("sample", "sample", sampleVector);
    return queryResult;
}
