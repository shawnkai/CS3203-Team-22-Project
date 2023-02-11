//
// Created by Jai Lulla  on 3/2/23.
//

#include <iostream>

#include "DesignEntityDatabase.h"

using namespace std;

/**
 * Adds the given Design Entity to the appropriate database.
 *
 * @param designEntityToBeStored The Design Entity "Reference" Object to be stored.
 */
void DesignEntityDatabase::addToDatabase(DesignEntity* designEntityToBeStored) {
    // First find the variable if it exists in db, if not, add.
    // If it does exist, then just retrieve and add to the vector<string> occurrence list

    if (this->isPresentInDatabase(designEntityToBeStored)) {
        this->updateEntityInDatabase(designEntityToBeStored);
    } else {
        (this->database).insert(make_pair((designEntityToBeStored->getNameOfEntity()), designEntityToBeStored));
    }
}

/**
 * Returns a boolean suggesting whether the given
 * Design Entity is already present in the database or not.
 *
 * @param designEntityToBeStored The Design Entity that is to be stored, and to be checked for.
 * @return A boolean, true, if the Entity already exists in the database.
 */
bool DesignEntityDatabase::isPresentInDatabase(DesignEntity* designEntityToBeStored) {
    return this->isPresentInDatabase(designEntityToBeStored->getNameOfEntity());
}

/**
 * Updates an existing Entity if already present in the database.
 *
 * @param designEntityToBeStored The Design Entity that is to be stored and/or updated.
 */
void DesignEntityDatabase::updateEntityInDatabase(DesignEntity* designEntityToBeStored) {
    // insert new set of value
//    (this->database)[designEntityToBeStored.getNameOfEntity()];

    auto iterator = (this->database).find(designEntityToBeStored->getNameOfEntity());
    (iterator->second)->addAdditionalOccurrence(designEntityToBeStored->getOccurrenceOfEntity()[0]);
    // Should the above line only copy the 0th index or copy the entire vector,
    // by indexing through it?

//    vector<string> toBeUpdated = (iterator->second).getOccurrenceOfEntity();
//    toBeUpdated.push_back(designEntityToBeStored.getOccurrenceOfEntity()[0]);
}

/**
 * Returns a boolean suggesting whether the given
 * Design Entity is already present in the database or not.
 *
 * @param entityName The Design Entity Name  that is to be checked for.
 * @return A boolean, true, if the Entity already exists in the database.
 */
bool DesignEntityDatabase::isPresentInDatabase(string entityName) {
    if ((this->database).find(entityName) == (this->database).end()) {
        return false;
    }
    return true;
}

/**
 * Returns a Result consisting of the Entity type queried for, given
 * by the name. If no Entity by that name is present, a Result is still
 * returned, but it consists of all "None" values.
 *
 * @param entityName The name of the Entity to be extracted.
 * @return A Result object, consisting of the Entity details, given by the Entity name.
 */
Result DesignEntityDatabase::getFromDatabase(string entityName) {
    if (this->isPresentInDatabase(entityName)) {
        auto iterator = (this->database).find(entityName);

        // Suggestion, overload result constructor to accept DesignEntity,
        // and let it parse

        return Result(
                (iterator->second)->getTypeOfEntity(),
                (iterator->second)->getNameOfEntity(),
                (iterator->second)->getOccurrenceOfEntity());
    }

    // Return None, as it was not found in Database (or throw an error)?
    vector<string> none{"None"};
    return Result("none", "none", none);
}

/**
 * Returns a vector consisting of all Entities of the given type
 * present in the database.
 *
 * @return A vector<Result> containing all the Entities of that Entity Type.
 */
vector<Result> DesignEntityDatabase::getAllFromDatabase() {
    vector<Result> resultVector;

    for (auto& [entityName, designEntity]: this->database) {
         resultVector.emplace_back(designEntity->getTypeOfEntity(),
                                   designEntity->getNameOfEntity(),
                                   designEntity->getOccurrenceOfEntity());
    }

    return resultVector;
}
