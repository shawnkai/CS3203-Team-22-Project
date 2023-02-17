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
    unordered_map<string, DesignEntity*> database;

    virtual bool isPresentInDatabase(DesignEntity* designEntityToBeStored);
    virtual void updateEntityInDatabase(DesignEntity* designEntityToBeStored);
    virtual bool isPresentInDatabase(string entityName);

public:

    virtual void addToDatabase(DesignEntity* designEntityToBeStored);
    virtual Result getFromDatabase(string entityName);
    virtual vector<Result> getAllFromDatabase();
};

#endif //SPA_DESIGNENTITYDATABASE_H
