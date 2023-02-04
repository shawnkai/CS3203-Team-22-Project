//
// Created by Jai Lulla  on 3/2/23.
//

#include <iostream>

#include "Variable.h"
#include "DesignEntitiesDatabase/DesignEntityDatabase.h"
#include "DesignEntitiesDatabase/DesignEntitiesDatabaseFactory.h"

using namespace std;

Variable::Variable(tuple<string, string> entityDetails) {
    this->nameOfEntity = get<0>(entityDetails);
    (this->occurrenceOfEntity).push_back(get<1>(entityDetails));
}

void Variable::addAdditionalOccurrence(string occurrence) {
    (this->occurrenceOfEntity).push_back(occurrence);
}

void Variable::addToDatabase() {
    // call storage/database factory and add, let storage check if there,
    // and update or add
    DesignEntityDatabase* database = DesignEntitiesDatabaseFactory::getEntityDatabase(this);
    database->addToDatabase(this);
}

string Variable::getNameOfEntity() {
    return this->nameOfEntity;
}

vector<string> Variable::getOccurrenceOfEntity() {
    return this->occurrenceOfEntity;
}

string Variable::getTypeOfEntity() {
    return "VARIABLE";
}
