//
// Created by Jai Lulla  on 2/2/23.
//

#include <iostream>

#include "DesignEntitiesFactory.h"
#include "Variable.h"
#include "Procedure.h"

using namespace std;

DesignEntity* DesignEntitiesFactory::createDesignEntity(string designEntity, tuple<string, string> entityDetails) {
    transform(designEntity.begin(), designEntity.end(), designEntity.begin(), ::toupper);

    if (designEntity == "PROCEDURE") {
        return new Procedure(entityDetails);
    } else if (designEntity == "VARIABLE") {
        return new Variable(entityDetails);
    } else if (designEntity == "CONSTANT") {

    } else if (designEntity == "STATEMENT") {

    } else if (designEntity == "READ") {

    } else if (designEntity == "PRINT") {

    } else if (designEntity == "ASSIGN") {

    } else if (designEntity == "CALL") {

    } else if (designEntity == "WHILE") {

    } else if (designEntity == "IF") {

    }

    // TEMP: Just to pass build
    return new Variable(entityDetails);
}
