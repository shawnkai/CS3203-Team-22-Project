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

/**
 * This method allows to add a Design Abstraction to the Program Knowledge Base.
 *
 * @param designAbstraction The type of abstraction that is to be added.
 * @param abstractionDetails A tuple, which takes in 3 strings. which contains the details about the abstraction.
 */
void PKB::addDesignAbstraction(string designAbstraction, tuple<string, string, string> abstractionDetails) {
    // To be implemented -> Done [05/02/2023]
    DesignAbstraction* da = DesignAbstractionsFactory::createDesignAbstraction(designAbstraction, abstractionDetails);
    da->addToDatabase();
}

/**
 * This method allows to add a Design Entity to the Program Knowledge Base.
 *
 * @param designEntity The type of entity that is to be added.
 * @param entityDetails A tuple, which takes in 2 strings, which contains the details about the entity.
 */
void PKB::addDesignEntity(string designEntity, tuple<string, string> entityDetails) {
    // To be implemented -> Done [05/02/2023]
    DesignEntity* de = DesignEntitiesFactory::createDesignEntity(designEntity, entityDetails);
    de->addToDatabase();
}

/**
 * Returns a Result Object, containing the Design Abstraction Details. These can
 * be accessed by the Result methods to be acted upon further.
 *
 * @param abstractionType Type of Abstraction to obtain.
 * @param query Query contains the eneity type being abstracted along with the entity name.
 * @return Result object with the result or "None" if the result does not exist.
 */
Result PKB::getDesignAbstraction(string abstractionType, tuple<string, string> query) {
    // To be implemented -> Done [05/02/2023]
    DesignAbstractionDatabase* db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase(abstractionType,
                                                                                              get<0>(query));
    Result queryResult = db->getFromDatabase(get<1>(query));

    return queryResult;
}

/**
 * Returns a Result Object, containing the Design Entity Details. These can be
 * accessed by the Result methods to be acted upon further.
 *
 * @param entityType Type of Entity to obtain.
 * @param entityName The name of the entity to be extracted.
 * @return Result object with the result or "None" if the result does not exist.
 */
Result PKB::getDesignEntity(string entityType, string entityName) {
    // To be implemented -> Done [05/02/2023]
    DesignEntityDatabase* db = DesignEntitiesDatabaseFactory::getEntityDatabase(entityType);
    Result queryResult = db->getFromDatabase(entityName);

    return queryResult;
}

/**
 * Returns a vector<Result>, containing all the Design Entity Details of that
 * Design Entity Type.
 *
 * @param entityType Type of Entity to obtain.
 * @return A vector<Result> with each Result Object containing the details of that entity type.
 */
vector<Result> PKB::getAllDesignEntity(string entityType) {
    // To be implemented
    vector<Result> queryResult;

    DesignEntityDatabase* db = DesignEntitiesDatabaseFactory::getEntityDatabase(entityType);
    queryResult = db->getAllFromDatabase();

    return queryResult;
}

Result PKB::getDesignEntity(string entityType, string entityName, string occurrenceLine) {
    // To be implemented

    // Demo Code
    vector<string> sampleVector(5, "");
    Result queryResult("sample", "sample", sampleVector);
    return queryResult;
}
