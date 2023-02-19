//
// Created by Jai Lulla  on 11/2/23.
//

#include <iostream>
#include <algorithm> // For Windows

#include "UsesFactory.h"
#include "AssignmentUses.h"
#include "PrintUses.h"
#include "ProcedureUses.h"
#include "StatementUses.h"
#include "ProcedureCallUses.h"
#include "WhileStatementUses.h"
#include "IfStatementUses.h"

using namespace std;

/**
 * Returns a DesignAbstraction pointer, related to the Uses Design Abstraction,
 * based on the type of entity being abstracted. A null pointer will be returned,
 * for invalid type of entities to be abstracted.
 *
 * @param abstractionDetails The details of the abstraction, that is to be stored.
 * @return A DesignAbstraction pointer, of type of Uses, depending on type of entity being abstracted.
 */
DesignAbstraction* UsesFactory::createUsesAbstraction(tuple<string, string, string> abstractionDetails) {
    string usesAbstractionType = get<0>(abstractionDetails);
    transform(usesAbstractionType.begin(), usesAbstractionType.end(), usesAbstractionType.begin(), ::toupper);

    if (usesAbstractionType == "ASSIGNMENT") {
        return new AssignmentUses(abstractionDetails);
    } else if (usesAbstractionType == "PRINT") {
        return new PrintUses(abstractionDetails);
    } else if (usesAbstractionType == "PROCEDURE") {
        return new ProcedureUses(abstractionDetails);
    } else if (usesAbstractionType == "STATEMENT") {
        return new StatementUses(abstractionDetails);
    } else if (usesAbstractionType == "PROCEDURECALL") {
        return new ProcedureCallUses(abstractionDetails);
    } else if (usesAbstractionType == "WHILE") {
        return new WhileStatementUses(abstractionDetails);
    } else if (usesAbstractionType == "IF") {
        return new IfStatementUses(abstractionDetails);
    }

    // Returning a null pointer, in case of an invalid usesAbstractionType
    return nullptr;
}
