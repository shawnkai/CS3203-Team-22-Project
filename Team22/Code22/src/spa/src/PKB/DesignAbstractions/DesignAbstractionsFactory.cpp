//
// Created by Jai Lulla  on 2/2/23.
//

#include <iostream>

#include "DesignAbstractionsFactory.h"
#include "ModifiesFactory.h"

using namespace std;

DesignAbstraction* DesignAbstractionsFactory::createDesignAbstraction(
        string designAbstraction, tuple<string, string, string> abstractionDetails) {
    transform(designAbstraction.begin(), designAbstraction.end(), designAbstraction.begin(), ::toupper);

    if (designAbstraction == "MODIFIES") {
        return ModifiesFactory::createModifiesAbstraction(abstractionDetails);
    }

    // To be implemented concretely
    return nullptr;
}
