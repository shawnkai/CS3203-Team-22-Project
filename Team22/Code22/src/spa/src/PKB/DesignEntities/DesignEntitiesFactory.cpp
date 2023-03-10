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
#include "AssignmentStatement.h"
#include "CallStatement.h"
#include "WhileStatement.h"
#include "IfStatement.h"

#include "PKB/Exceptions/InvalidEntityTypeException.cpp"

using namespace std;

/**
 * Returns a DesignEntity pointer, which is created, based on the parameters passed in. If an
 * invalid Design Entity name is passed in, a null pointer is returned.
 *
 * @param designEntity The type of the Design Entity, whose pointer is to be created.
 * @param entityDetails The details to be stored in the created Design Entity.
 * @return A DesignEntity pointer, based on the parameters passed in.
 */
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
    } else if (designEntity == "ASSIGNMENT") {
        return new AssignmentStatement(entityDetails);
    } else if (designEntity == "CALL") {
        return new CallStatement(entityDetails);
    } else if (designEntity == "WHILE") {
        return new WhileStatement(entityDetails);
    } else if (designEntity == "IF") {
        return new IfStatement(entityDetails);
    }

    throw InvalidEntityTypeException((designEntity + " is not a valid Design Entity Type").data());
}
