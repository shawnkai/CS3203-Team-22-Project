//
// Created by Jai Lulla  on 3/2/23.
//

#pragma once

#ifndef SPA_VARIABLEDATABASE_H
#define SPA_VARIABLEDATABASE_H

#include <iostream>

#include "DesignEntityDatabase.h"

using namespace std;

class VariableDatabase: public DesignEntityDatabase {
public:
    void addToDatabase(DesignEntity* designEntityToBeStored) override;
    bool isPresentInDatabase(DesignEntity* designEntityToBeStored) override;
    void updateEntityInDatabase(DesignEntity* designEntityToBeStored) override;
    bool isPresentInDatabase(string entityName) override;
    Result getFromDatabase(string entityName) override;
};

#endif //SPA_VARIABLEDATABASE_H
