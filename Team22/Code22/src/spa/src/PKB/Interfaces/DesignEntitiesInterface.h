//
// Created by Jai Lulla  on 30/3/23.
//

#pragma once

#ifndef SPA_DESIGNENTITIESINTERFACE_H
#define SPA_DESIGNENTITIESINTERFACE_H

#include <iostream>

#include "Result.h"

using namespace std;

class DesignEntitiesInterface {
public:
    void addDesignEntity(string designEntity, tuple<string, string> entityDetails);
    Result getDesignEntity(string entityType, string entityName);
    vector<Result> getAllDesignEntity(string entityType);
    int getNumberOfDesignEntity(string entityType);
};

#endif //SPA_DESIGNENTITIESINTERFACE_H
