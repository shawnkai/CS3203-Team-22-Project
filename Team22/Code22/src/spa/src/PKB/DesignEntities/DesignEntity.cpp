//
// Created by Jai Lulla  on 2/2/23.
//

#include <iostream>

#include "DesignEntity.h"
#include "DesignEntitiesDatabase/DesignEntityDatabase.h"
#include "DesignEntitiesDatabase/DesignEntitiesDatabaseFactory.h"

using namespace std;

/**
 * Creates a Design Entity with the given details,
 *
 * @param entityDetails This encompasses the details of the Entity to be created.
 */
DesignEntity::DesignEntity(tuple<string, string> entityDetails) {
    this->nameOfEntity = get<0>(entityDetails);
    (this->occurrenceOfEntity).push_back(get<1>(entityDetails));
}

bool DesignEntity::isOccurrencePresent(string occurrence) {
    return (find(this->occurrenceOfEntity.begin(), this->occurrenceOfEntity.end(), occurrence))
           != (this->occurrenceOfEntity.end());
}

/**
 * If the Database finds out that the Entity is already stored in the
 * Database, it calls this method, to append additional occurrences.
 *
 * @param occurrence The occurrence to be appended.
 */
void DesignEntity::addAdditionalOccurrence(string occurrence) {
    if (!this->isOccurrencePresent(occurrence)) {
        (this->occurrenceOfEntity).push_back(occurrence);
    }
}

/**
 * Returns the name of the Entity.
 *
 * @return The name of the Entity.
 */
string DesignEntity::getNameOfEntity() {
    return this->nameOfEntity;
}

/**
 * Returns a vector<string>, that contains the occurrences of
 * this Entity.
 *
 * @return A vector<string> encompassing the occurrences of the Entity.
 */
vector<string> DesignEntity::getOccurrenceOfEntity() {
    return this->occurrenceOfEntity;
}
