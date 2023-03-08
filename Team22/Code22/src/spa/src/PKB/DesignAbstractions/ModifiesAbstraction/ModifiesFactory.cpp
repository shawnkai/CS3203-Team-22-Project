//
// Created by Jai Lulla  on 5/2/23.
//

#include <iostream>
#include <algorithm> // For Windows

#include "ModifiesFactory.h"
#include "PKB/DesignAbstractions/ModifiesAbstraction/AssignmentModifies.h"
#include "PKB/DesignAbstractions/ModifiesAbstraction/ReadModifies.h"
#include "PKB/DesignAbstractions/ModifiesAbstraction/StatementModifies.h"
#include "PKB/DesignAbstractions/ModifiesAbstraction/ProcedureModifies.h"
#include "PKB/DesignAbstractions/ModifiesAbstraction/ProcedureCallModifies.h"
#include "PKB/DesignAbstractions/ModifiesAbstraction/IfStatementModifies.h"
#include "PKB/DesignAbstractions/ModifiesAbstraction/WhileStatementModifies.h"

#include "PKB/Exceptions/InvalidModifiesAbstractionTypeException.cpp"

using namespace std;

/**
 * Returns a DesignAbstraction pointer, related to the Modifies Design Abstraction,
 * based on the type of entity being abstracted. A null pointer will be returned,
 * for invalid type of entities to be abstracted.
 *
 * @param abstractionDetails The details of the abstraction, that is to be stored.
 * @return A DesignAbstraction pointer, of type of Modifies, depending on type of entity being abstracted.
 */
DesignAbstraction* ModifiesFactory::createModifiesAbstraction(tuple<string, string, string> abstractionDetails) {
    // Design choice, pass 1st param as type of modifies? -> think

    string modifiesAbstractionType = get<0>(abstractionDetails);
    transform(modifiesAbstractionType.begin(), modifiesAbstractionType.end(), modifiesAbstractionType.begin(), ::toupper);

    if (modifiesAbstractionType == "ASSIGNMENT") {
        return new AssignmentModifies(abstractionDetails);
    } else if (modifiesAbstractionType == "READ") {
        return new ReadModifies(abstractionDetails);
    } else if (modifiesAbstractionType == "STATEMENT") {
        return new StatementModifies(abstractionDetails);
    } else if (modifiesAbstractionType == "PROCEDURE") {
        return new ProcedureModifies(abstractionDetails);
    } else if (modifiesAbstractionType == "PROCEDURECALL") {
        return new ProcedureCallModifies(abstractionDetails);
    } else if (modifiesAbstractionType == "IF") {
        return new IfStatementModifies(abstractionDetails);
    } else if (modifiesAbstractionType == "WHILE") {
        return new WhileStatementModifies(abstractionDetails);
    }

    throw InvalidModifiesAbstractionTypeException((modifiesAbstractionType + " is not a valid Modifies Design Abstraction Type").data());
}
