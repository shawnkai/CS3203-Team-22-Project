//
// Created by Jai Lulla  on 5/2/23.
//

#include <iostream>
#include <algorithm>

#include "AssignmentModifies.h"
#include "ModifiesFactory.h"
#include "ReadModifies.h"
#include "StatementModifies.h"
#include "ProcedureModifies.h"
#include "ProcedureCallModifies.h"

using namespace std;

DesignAbstraction* ModifiesFactory::createModifiesAbstraction(tuple<string, string, string> abstractionDetails) {
    // To be implemented
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
    }

    // TEMP: to pass build,
    // also to return this, implying wrong modifiesAbstractionType
    // Catch it somewhere?
    return nullptr;
}
