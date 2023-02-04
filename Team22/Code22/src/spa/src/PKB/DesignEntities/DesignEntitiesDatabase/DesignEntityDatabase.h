//
// Created by Jai Lulla  on 3/2/23.
//

#pragma once

#ifndef SPA_DESIGNENTITYDATABASE_H
#define SPA_DESIGNENTITYDATABASE_H

#include <iostream>
#include <unordered_map>

#include "../DesignEntity.h"
#include "../../../Result.h"

using namespace std;

class DesignEntityDatabase {
public:
    unordered_map<string, DesignEntity*> database;

    virtual void addToDatabase(DesignEntity* designEntityToBeStored) = 0;
    virtual bool isPresentInDatabase(DesignEntity* designEntityToBeStored) = 0;
    virtual void updateEntityInDatabase(DesignEntity* designEntityToBeStored) = 0;
    virtual bool isPresentInDatabase(string entityName) = 0;
    virtual Result getFromDatabase(string entityName) = 0;
};

#endif //SPA_DESIGNENTITYDATABASE_H
