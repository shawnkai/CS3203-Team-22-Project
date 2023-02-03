//
// Created by Jai Lulla  on 2/2/23.
//

#include <iostream>

#include "DesignEntitiesFactory.h"
#include "Variable.h"

using namespace std;

DesignEntity DesignEntitiesFactory::createDesignEntity(string designEntity, tuple<string, string> entityDetails) {
    transform(designEntity.begin(), designEntity.end(), designEntity.begin(), ::tolower);

    if (designEntity == "procedure") {

    } else if (designEntity == "variable") {
        return Variable(entityDetails);
    } else if (designEntity == "constant") {

    } else if (designEntity == "statement") {

    } else if (designEntity == "read") {

    } else if (designEntity == "print") {

    } else if (designEntity == "assign") {

    } else if (designEntity == "call") {

    } else if (designEntity == "while") {

    } else if (designEntity == "if") {

    }

    // Just to pass build - temp
    return Variable(entityDetails);
}
