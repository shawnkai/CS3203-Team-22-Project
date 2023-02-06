//
// Created by Jai Lulla  on 4/2/23.
//

#include <iostream>

#include "DesignAbstractionDatabase.h"

using namespace std;

void DesignAbstractionDatabase::addToDatabase(DesignAbstraction *designAbstractionToBeStored) {
    if (this->isPresentInDatabase(designAbstractionToBeStored)) {
        this->updateAbstractionInDatabase(designAbstractionToBeStored);
    } else {
        (this->abstractionDatabase).insert(
                make_pair(designAbstractionToBeStored->getEntityName(),
                          designAbstractionToBeStored));
    }
}

bool DesignAbstractionDatabase::isPresentInDatabase(DesignAbstraction *designAbstractionToBeStored) {
    return this->isPresentInDatabase(designAbstractionToBeStored->getEntityName());
}

bool DesignAbstractionDatabase::isPresentInDatabase(string entityName) {
    if ((this->abstractionDatabase).find(entityName) == (this->abstractionDatabase).end()) {
        return false;
    }
    return true;
}

void DesignAbstractionDatabase::updateAbstractionInDatabase(DesignAbstraction *designAbstractionToBeStored) {
    auto iterator = (this->abstractionDatabase).find(designAbstractionToBeStored->getEntityName());
    (iterator->second)->addAdditionalOccurrence(designAbstractionToBeStored->getEntityOccurrence()[0]);
    // Should the above line only copy the 0th index or
    // copy the entire vector, by indexing through it?
}

Result DesignAbstractionDatabase::getFromDatabase(string entityName) {
    // Should Result be modified to accommodate DesignAbstraction?

    if (this->isPresentInDatabase(entityName)) {
        auto iterator = (this->abstractionDatabase).find(entityName);

        // Suggestion, overload result constructor to accept DesignAbstraction,
        // and let it parse
//        return Result(
//                ((iterator->second)->getTypeOfAbstraction() + "/" + (iterator->second)->getEntityTypeBeingAbstracted()),
//                (iterator->second)->getEntityName(),
//                (iterator->second)->getEntityOccurrence());

        return Result(
                ((iterator->second)->getTypeOfAbstraction()),
                (iterator->second)->getEntityName(),
                (iterator->second)->getEntityOccurrence());
    }

    // Return None, as it was not found in Database (or throw an error)?
    vector<string> none{"None"};
    return Result("none", "none", none);
}

