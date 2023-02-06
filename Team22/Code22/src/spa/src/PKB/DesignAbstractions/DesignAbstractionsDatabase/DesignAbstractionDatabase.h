//
// Created by Jai Lulla  on 4/2/23.
//

#pragma once

#ifndef SPA_DESIGNABSTRACTIONDATABASE_H
#define SPA_DESIGNABSTRACTIONDATABASE_H

#include <iostream>
#include <unordered_map>

#include "../DesignAbstraction.h"
#include "../../../Result.h"

using namespace std;

class DesignAbstractionDatabase {
    unordered_map<string, DesignAbstraction*> abstractionDatabase;

public:
    virtual void addToDatabase(DesignAbstraction* designAbstractionToBeStored);
    virtual Result getFromDatabase(string entityName);
    virtual bool isPresentInDatabase(DesignAbstraction* designAbstractionToBeStored);
    virtual bool isPresentInDatabase(string entityName);
    virtual void updateAbstractionInDatabase(DesignAbstraction* designAbstractionToBeStored);
};


#endif //SPA_DESIGNABSTRACTIONDATABASE_H
