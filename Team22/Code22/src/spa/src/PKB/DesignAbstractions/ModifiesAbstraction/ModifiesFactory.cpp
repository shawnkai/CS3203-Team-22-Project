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
#include "PKB/DesignAbstractions/ModifiesAbstraction/WhileStatementModifies.h"

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
    } else if (modifiesAbstractionType == "IF") {

    } else if (modifiesAbstractionType == "WHILE") {
        return new WhileStatementModifies(abstractionDetails);
    }

    // TEMP: to pass build,
    // also to return this, implying wrong modifiesAbstractionType
    // Catch it somewhere?
    return nullptr;
}
