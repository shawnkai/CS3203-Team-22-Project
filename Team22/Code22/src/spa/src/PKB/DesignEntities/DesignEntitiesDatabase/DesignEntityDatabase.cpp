//
// Created by Jai Lulla  on 3/2/23.
//

#include <iostream>

#include "DesignEntityDatabase.h"

using namespace std;

void DesignEntityDatabase::addToDatabase(DesignEntity* designEntityToBeStored) {
    // First find the variable if it exists in db, if not, add.
    // If it does exist, then just retrieve and add to the vector<string> occurrence list

    if (this->isPresentInDatabase(designEntityToBeStored)) {
        this->updateEntityInDatabase(designEntityToBeStored);
    } else {
        (this->database).insert(make_pair((designEntityToBeStored->getNameOfEntity()), designEntityToBeStored));
    }
}

bool DesignEntityDatabase::isPresentInDatabase(DesignEntity* designEntityToBeStored) {
    return this->isPresentInDatabase(designEntityToBeStored->getNameOfEntity());
}

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

bool DesignEntityDatabase::isPresentInDatabase(string entityName) {
    if ((this->database).find(entityName) == (this->database).end()) {
        return false;
    }
    return true;
}

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
