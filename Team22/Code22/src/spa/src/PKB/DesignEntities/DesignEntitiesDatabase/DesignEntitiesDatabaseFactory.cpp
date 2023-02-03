//
// Created by Jai Lulla  on 3/2/23.
//

#include <iostream>

#include "DesignEntitiesDatabaseFactory.h"
#include "../Variable.h"

using namespace std;

DesignEntityDatabase DesignEntitiesDatabaseFactory::getEntityDatabase(DesignEntity designEntity) {
    if (designEntity.getTypeOfEntity() == "VARIABLE") {
        return variableEntitiesDatabase;
    }

    // TEMP: For building purposes
    return variableEntitiesDatabase;
}
