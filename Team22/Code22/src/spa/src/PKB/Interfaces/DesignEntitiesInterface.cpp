//
// Created by Jai Lulla  on 30/3/23.
//

#include <iostream>

#include "DesignEntitiesInterface.h"

#include "PKB/DesignEntities/DesignEntitiesDatabase/DesignEntitiesDatabaseFactory.h"
#include "PKB/DesignEntities/DesignEntitiesDatabase/DesignEntityDatabase.h"
#include "PKB/DesignEntities/DesignEntitiesFactory.h"

using namespace std;

/**
 * This method allows to add a Design Entity to the Program Knowledge Base.
 *
 * @param designEntity The type of Design Entity that is to be added.
 * @param entityDetails A tuple, which takes in 2 strings, which contains the details about the Design Entity.
 */
void DesignEntitiesInterface::addDesignEntity(string designEntity, tuple<string, string> entityDetails) {
    DesignEntity *de = DesignEntitiesFactory::createDesignEntity(designEntity, entityDetails);
    DesignEntityDatabase *db = DesignEntitiesDatabaseFactory::getEntityDatabase(de);

    db->addToDatabase(de);
}

/**
 * Returns a Result Object, containing the Design Entity Details. These can be
 * accessed by the Result methods to be acted upon further.
 *
 * @param entityType Type of Entity to obtain.
 * @param entityName The name of the Design Entity to be extracted.
 * @return Result object with the result or "None" if the result does not exist.
 */
Result DesignEntitiesInterface::getDesignEntity(string entityType, string entityName) {
    DesignEntityDatabase *db = DesignEntitiesDatabaseFactory::getEntityDatabase(entityType);
    Result queryResult = db->getFromDatabase(entityName);

    return queryResult;
}

/**
 * Returns a vector<Result>, containing all the Design Entity Details of that
 * Design Entity Type.
 *
 * @param entityType The type of Design Entity to obtain.
 * @return A vector<Result> with each Result Object containing the details of that Design Entity type.
 */
vector<Result> DesignEntitiesInterface::getAllDesignEntity(string entityType) {
    vector<Result> queryResult;

    DesignEntityDatabase *db = DesignEntitiesDatabaseFactory::getEntityDatabase(entityType);
    queryResult = db->getAllFromDatabase();

    return queryResult;
}

int DesignEntitiesInterface::getNumberOfDesignEntity(string entityType) {
    return this->getAllDesignEntity(entityType).size();
}
