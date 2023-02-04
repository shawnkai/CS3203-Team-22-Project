//
// Created by Jai Lulla  on 3/2/23.
//

#include <iostream>

#include "VariableDatabase.h"

using namespace std;

void VariableDatabase::addToDatabase(DesignEntity* designEntityToBeStored) {
    // First find the variable if it exists in db, if not, add.
    // If it does exist, then just retrieve and add to the vector<string> occurrence list

    if (this->isPresentInDatabase(designEntityToBeStored)) {
        this->updateEntityInDatabase(designEntityToBeStored);
    } else {
        (this->database).insert(make_pair((designEntityToBeStored->getNameOfEntity()), designEntityToBeStored));
    }
}

bool VariableDatabase::isPresentInDatabase(DesignEntity* designEntityToBeStored) {
    return this->isPresentInDatabase(designEntityToBeStored->getNameOfEntity());
}

void VariableDatabase::updateEntityInDatabase(DesignEntity* designEntityToBeStored) {
    // insert new set of value
//    (this->database)[designEntityToBeStored.getNameOfEntity()];

    auto iterator = (this->database).find(designEntityToBeStored->getNameOfEntity());
    (iterator->second)->addAdditionalOccurrence(designEntityToBeStored->getOccurrenceOfEntity()[0]);

//    vector<string> toBeUpdated = (iterator->second).getOccurrenceOfEntity();
//    toBeUpdated.push_back(designEntityToBeStored.getOccurrenceOfEntity()[0]);
}

bool VariableDatabase::isPresentInDatabase(string entityName) {
    if ((this->database).find(entityName) == (this->database).end()) {
        return false;
    }
    return true;
}

Result VariableDatabase::getFromDatabase(string entityName) {
    if (this->isPresentInDatabase(entityName)) {
        auto iterator = (this->database).find(entityName);

        // Suggestion, overload result constructor to accept DesignEntity,
        // and let it parse

        return Result(
                (iterator->second)->getTypeOfEntity(),
                (iterator->second)->getNameOfEntity(),
                (iterator->second)->getOccurrenceOfEntity());
    }

    // Return None, as it was not found in Database
    vector<string> none{"None"};
    return Result("none", "none", none);
}
