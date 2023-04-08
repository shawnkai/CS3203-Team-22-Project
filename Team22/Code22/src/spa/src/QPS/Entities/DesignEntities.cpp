//
// Created by Atin Sakkeer Hussain on 01/02/2023.
//

#include "DesignEntities.h"
#include "Utilities.h"

// Design Entity
DesignEntity::DesignEntity(string entityType) {
    this->entityType = std::move(entityType);
};

string DesignEntity::getType() const {
    return this->entityType;
}

DesignEntity::DesignEntity() {}