//
// Created by Jai Lulla  on 3/2/23.
//

#include <iostream>
#include <algorithm> // For Windows

#include "DesignEntitiesDatabaseFactory.h"

using namespace std;

DesignEntityDatabase* DesignEntitiesDatabaseFactory::getEntityDatabase(DesignEntity* designEntity) {
    return getEntityDatabase(designEntity->getTypeOfEntity());
}

DesignEntityDatabase* DesignEntitiesDatabaseFactory::getEntityDatabase(string designEntityType) {
    transform(designEntityType.begin(), designEntityType.end(), designEntityType.begin(), ::toupper);

    if (designEntityType == "VARIABLE") {
        return variableEntitiesDatabase;
    } else if (designEntityType == "PROCEDURE") {
        return procedureEntitiesDatabase;
    } else if (designEntityType == "STATEMENT") {
        return statementEntitiesDatabase;
    } else if (designEntityType == "READ") {
        return readStatementEntitiesDatabase;
    } else if (designEntityType == "CONSTANT") {
        return constantEntitiesDatabase;
    } else if (designEntityType == "PRINT") {
        return printStatementEntitiesDatabase;
    } else if (designEntityType == "ASSIGN") {
        return assignStatementEntitiesDatabase;
    }

    // TEMP: For building purposes
    return nullptr;
}
