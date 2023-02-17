//
// Created by Jai Lulla  on 2/2/23.
//

#include <iostream>

#include "DesignAbstraction.h"
#include "DesignAbstractionsDatabase/DesignAbstractionDatabase.h"
#include "DesignAbstractionsDatabase/DesignAbstractionsDatabaseFactory.h"

using namespace std;

DesignAbstraction::DesignAbstraction(tuple<string, string, string> abstractionDetails) {
    this->entityTypeBeingAbstracted = get<0>(abstractionDetails);
    this->entityName = get<1>(abstractionDetails);
    (this->entityOccurrences).push_back(get<2>(abstractionDetails));
}

bool DesignAbstraction::isOccurrencePresent(string entityOccurrence) {
    return (find(this->entityOccurrences.begin(), this->entityOccurrences.end(), entityOccurrence))
                                                                != (this->entityOccurrences.end());
}

void DesignAbstraction::addToDatabase() {
    // Error caused here maybe
    DesignAbstractionDatabase* database = DesignAbstractionsDatabaseFactory::getAbstractionDatabase(this);
    database->addToDatabase(this);
}

void DesignAbstraction::addAdditionalOccurrence(string entityOccurrence) {
    if (!this->isOccurrencePresent(entityOccurrence)) {
        (this->entityOccurrences).push_back(entityOccurrence);
    }
}

string DesignAbstraction::getEntityTypeBeingAbstracted() {
    return (this->entityTypeBeingAbstracted);
}

string DesignAbstraction::getEntityName() {
    return (this->entityName);
}

vector<string> DesignAbstraction::getEntityOccurrence() {
    return (this->entityOccurrences);
}
