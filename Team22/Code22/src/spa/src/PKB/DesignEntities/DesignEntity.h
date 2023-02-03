//
// Created by Jai Lulla  on 2/2/23.
//
#pragma once

#ifndef SPA_DESIGNENTITY_H
#define SPA_DESIGNENTITY_H

#include <iostream>
#include <vector>

using namespace std;

// The factory will look up table, if found the entity, just push the data into
// occurrence of the entity, else create a new one, and then push that into table

class DesignEntity {
public:
    string nameOfEntity;
    vector<string> occurrenceOfEntity;

    virtual void addAdditionalOccurrence(string occurrence) = 0;
//    virtual void addToDatabase(DesignEntity designEntityCreated);
    virtual void addToDatabase() = 0;
    virtual string getNameOfEntity() = 0;
    virtual vector<string> getOccurrenceOfEntity() = 0;
    virtual string getTypeOfEntity() = 0;
};

#endif //SPA_DESIGNENTITY_H
