//
// Created by Jai Lulla  on 2/2/23.
//

#include <iostream>

#include "DesignEntity.h"
#include "DesignEntitiesDatabase/DesignEntityDatabase.h"
#include "DesignEntitiesDatabase/DesignEntitiesDatabaseFactory.h"

using namespace std;

DesignEntity::DesignEntity(tuple<string, string> entityDetails) {
    this->nameOfEntity = get<0>(entityDetails);
    (this->occurrenceOfEntity).push_back(get<1>(entityDetails));
}

void DesignEntity::addAdditionalOccurrence(string occurrence) {
    (this->occurrenceOfEntity).push_back(occurrence);
}

void DesignEntity::addToDatabase() {
    // call storage/database factory and add, let storage check if there,
    // and update or add
    DesignEntityDatabase* database = DesignEntitiesDatabaseFactory::getEntityDatabase(this);
    database->addToDatabase(this);
}

string DesignEntity::getNameOfEntity() {
    return this->nameOfEntity;
}

vector<string> DesignEntity::getOccurrenceOfEntity() {
    return this->occurrenceOfEntity;
}
