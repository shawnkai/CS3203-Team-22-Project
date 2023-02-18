//
// Created by Jai Lulla  on 2/2/23.
//

#include <iostream>

#include "DesignAbstraction.h"
#include "DesignAbstractionsDatabase/DesignAbstractionDatabase.h"
#include "DesignAbstractionsDatabase/DesignAbstractionsDatabaseFactory.h"

using namespace std;

/**
 * Creates a Design Abstraction Object, with the tuple <string, string, string>.
 * The first parameter of the tuple holds the entity type that is being abstracted.
 * The second parameter of the tuple holds the name of the entity.
 * The third parameter of the tuple holds the occurrence of the given abstraction.
 *
 * @param abstractionDetails A tuple holding the details of the design abstraction.
 */
DesignAbstraction::DesignAbstraction(tuple<string, string, string> abstractionDetails) {
    this->entityTypeBeingAbstracted = get<0>(abstractionDetails);
    this->entityName = get<1>(abstractionDetails);
    (this->entityOccurrences).push_back(get<2>(abstractionDetails));
}

/**
 * Returns true, if the given occurrence being looked up for, exists in the occurrence vector,
 * else returns false.
 *
 * @param entityOccurrence The entity occurrence being looked up for.
 * @return True, if the occurrence exists, else false.
 */
bool DesignAbstraction::isOccurrencePresent(string entityOccurrence) {
    return (find(this->entityOccurrences.begin(), this->entityOccurrences.end(), entityOccurrence))
                                                                != (this->entityOccurrences.end());
}

/**
 * Adds the created Design Abstraction object to the database.
 */
void DesignAbstraction::addToDatabase() {
    DesignAbstractionDatabase* database = DesignAbstractionsDatabaseFactory::getAbstractionDatabase(this);
    database->addToDatabase(this);
}

/**
 * Adds the given additional occurrence of an entity. If it already exists in the database,
 * it is not added, as it is considered a duplicate.
 *
 * @param entityOccurrence The additional occurrence of the entity to be added.
 */
void DesignAbstraction::addAdditionalOccurrence(string entityOccurrence) {
    if (!this->isOccurrencePresent(entityOccurrence)) {
        (this->entityOccurrences).push_back(entityOccurrence);
    }
}

/**
 * Returns the type of entity that is being abstracted here, by the given Design Abstraction.
 *
 * @return A string containing the type of entity being abstracted.
 */
string DesignAbstraction::getEntityTypeBeingAbstracted() {
    return (this->entityTypeBeingAbstracted);
}

/**
 * Returns the name of the entity that is being abstracted, by the given Design Abstraction.
 * 
 * @return A string containing the name of the entity.
 */
string DesignAbstraction::getEntityName() {
    return (this->entityName);
}

/**
 * Returns a vector of strings, containing all the occurrences of the entity of the given name
 * and the given Design Abstraction. An empty vector might be returned, if no
 * occurrences are present.
 *
 * @return A vector of strings containing the occurrences, else an empty vector.
 */
vector<string> DesignAbstraction::getEntityOccurrence() {
    return (this->entityOccurrences);
}
