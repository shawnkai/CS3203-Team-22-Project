//
// Created by Jai Lulla  on 2/2/23.
//

#include <iostream>
#include <algorithm> // For Windows

#include "DesignAbstractionsFactory.h"
#include "PKB/DesignAbstractions/ModifiesAbstraction/ModifiesFactory.h"

using namespace std;

/**
 * Returns a DesignAbstraction Pointer Object, which is created by passing
 * in the relevant arguments.
 *
 * @param designAbstraction The type of Abstraction to be created.
 * @param abstractionDetails The details that the Abstraction Carries.
 * @return DesignAbstraction* Pointer Object, which stores the Abstraction Details passed, provided they are relevant.
 */
DesignAbstraction* DesignAbstractionsFactory::createDesignAbstraction(
        string designAbstraction, tuple<string, string, string> abstractionDetails) {
    transform(designAbstraction.begin(), designAbstraction.end(), designAbstraction.begin(), ::toupper);

    if (designAbstraction == "MODIFIES") {
        return ModifiesFactory::createModifiesAbstraction(abstractionDetails);
    }

    // To be implemented concretely
    return nullptr;
}
