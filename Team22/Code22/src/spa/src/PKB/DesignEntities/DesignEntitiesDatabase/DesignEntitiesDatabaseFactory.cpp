//
// Created by Jai Lulla  on 3/2/23.
//

#include <iostream>

#include "DesignEntitiesDatabaseFactory.h"

using namespace std;

DesignEntityDatabase* DesignEntitiesDatabaseFactory::getEntityDatabase(DesignEntity* designEntity) {
    return getEntityDatabase(designEntity->getTypeOfEntity());
}

DesignEntityDatabase* DesignEntitiesDatabaseFactory::getEntityDatabase(string designEntityType) {
    // Make string toupper

    if (designEntityType == "VARIABLE") {
        return variableEntitiesDatabase;
    } else if (designEntityType == "PROCEDURE") {
        return procedureEntitiesDatabase;
    }

    // TEMP: For building purposes
    return variableEntitiesDatabase;
}
