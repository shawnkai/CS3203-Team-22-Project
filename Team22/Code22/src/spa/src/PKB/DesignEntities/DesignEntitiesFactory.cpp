//
// Created by Jai Lulla  on 2/2/23.
//

#include <iostream>
#include <algorithm> // For Windows

#include "DesignEntitiesFactory.h"
#include "Variable.h"
#include "Procedure.h"
#include "Statement.h"
#include "ReadStatement.h"
#include "Constant.h"
#include "PrintStatement.h"
#include "AssignStatement.h"
#include "CallStatement.h"

using namespace std;

DesignEntity* DesignEntitiesFactory::createDesignEntity(string designEntity, tuple<string, string> entityDetails) {
    transform(designEntity.begin(), designEntity.end(), designEntity.begin(), ::toupper);

    if (designEntity == "PROCEDURE") {
        return new Procedure(entityDetails);
    } else if (designEntity == "VARIABLE") {
        return new Variable(entityDetails);
    } else if (designEntity == "CONSTANT") {
        return new Constant(entityDetails);
    } else if (designEntity == "STATEMENT") {
        return new Statement(entityDetails);
    } else if (designEntity == "READ") {
        return new ReadStatement(entityDetails);
    } else if (designEntity == "PRINT") {
        return new PrintStatement(entityDetails);
    } else if (designEntity == "ASSIGN") {
        return new AssignStatement(entityDetails);
    } else if (designEntity == "CALL") {
        return new CallStatement(entityDetails);
    } else if (designEntity == "WHILE") {

    } else if (designEntity == "IF") {

    }

    // TEMP: Just to pass build
    return nullptr;
}
