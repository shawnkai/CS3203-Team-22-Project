//
// Created by Jai Lulla  on 3/2/23.
//

#include <iostream>

#include "VariableDatabase.h"

using namespace std;

void VariableDatabase::addToDatabase(DesignEntity designEntityToBeStored) {
    // First find the variable if it exists in db, if not, add.
    // If does exist, then just retrieve and add to the vector<string> occurrence list

    if (this->isPresentInDatabase(designEntityToBeStored)) {
        this->updateEntityInDatabase(designEntityToBeStored);
    } else {
        (this->database).insert(make_pair(designEntityToBeStored.getNameOfEntity(), designEntityToBeStored));
    }
}

bool VariableDatabase::isPresentInDatabase(DesignEntity designEntityToBeStored) {
    if ((this->database).find(designEntityToBeStored.getNameOfEntity()) == (this->database).end()) {
        return false;
    }
    return true;
}

void VariableDatabase::updateEntityInDatabase(DesignEntity designEntityToBeStored) {
    // insert new set of value
//    (this->database)[designEntityToBeStored.getNameOfEntity()];

    auto iterator = (this->database).find(designEntityToBeStored.getNameOfEntity());
    (iterator->second).addAdditionalOccurrence(designEntityToBeStored.getOccurrenceOfEntity()[0]);

//    vector<string> toBeUpdated = (iterator->second).getOccurrenceOfEntity();
//    toBeUpdated.push_back(designEntityToBeStored.getOccurrenceOfEntity()[0]);
}
