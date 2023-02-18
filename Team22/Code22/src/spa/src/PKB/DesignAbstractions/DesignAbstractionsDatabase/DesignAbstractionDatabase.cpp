//
// Created by Jai Lulla  on 4/2/23.
//

#include <iostream>

#include "DesignAbstractionDatabase.h"

using namespace std;

/**
 * Adds the given Design Abstraction pointer to the database.
 *
 * @param designAbstractionToBeStored The Design Abstraction pointer to be stored.
 */
void DesignAbstractionDatabase::addToDatabase(DesignAbstraction *designAbstractionToBeStored) {
    if (this->isPresentInDatabase(designAbstractionToBeStored)) {
        this->updateAbstractionInDatabase(designAbstractionToBeStored);
    } else {
        (this->abstractionDatabase).insert(
                make_pair(designAbstractionToBeStored->getEntityName(),
                          designAbstractionToBeStored));
    }
}

/**
 * Returns true, if the Design Abstraction, that is to be stored, is already present in
 * the database, or has a pointer of the same Design Abstraction, with the same Design Entity
 * name stored, else returns false.
 *
 * @param designAbstractionToBeStored The Design Abstraction pointer to be checked.
 * @return A boolean, true, if the Design Abstraction with the same Design Entity name is present, else false.
 */
bool DesignAbstractionDatabase::isPresentInDatabase(DesignAbstraction *designAbstractionToBeStored) {
    return this->isPresentInDatabase(designAbstractionToBeStored->getEntityName());
}

/**
 * Returns true, if the Design Abstractions Design Entity Name, that is to be stored,
 * is already present in the database, else returns false.
 *
 * @param entityName The name of the Design Entity to check for.
 * @return A boolean, true, if the Design Abstraction with the same Design Entity name is present, else false.
 */
bool DesignAbstractionDatabase::isPresentInDatabase(string entityName) {
    if ((this->abstractionDatabase).find(entityName) == (this->abstractionDatabase).end()) {
        return false;
    }
    return true;
}

/**
 * Updates the occurrence vector, by adding new occurrences that are found, with the same
 * Design Abstraction Type, and same Design Entity name, and helps to avoid duplication.
 *
 * @param designAbstractionToBeStored The Design Abstraction pointer, from which the details are to be extracted.
 */
void DesignAbstractionDatabase::updateAbstractionInDatabase(DesignAbstraction *designAbstractionToBeStored) {
    auto iterator = (this->abstractionDatabase).find(designAbstractionToBeStored->getEntityName());
    (iterator->second)->addAdditionalOccurrence(designAbstractionToBeStored->getEntityOccurrence()[0]);
    // Should the above line only copy the 0th index or
    // copy the entire vector, by indexing through it?

    // maybe delete the pointer object here
}

/**
 * Returns a Result object, containing the details of the Design Abstraction obtained,
 * based on the Design Entity Name passed in. A Result Object with all "None", might be
 * returned, in case the Design Abstraction with the Design Entity name being looked up
 * for could not be found.
 *
 * @param entityName The name of the Design Entity to query the database for.
 * @return A Result object, with the result of the query, or a none Result object.
 */
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

