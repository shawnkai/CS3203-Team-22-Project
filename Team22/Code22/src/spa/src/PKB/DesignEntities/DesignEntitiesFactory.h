//
// Created by Jai Lulla  on 2/2/23.
//
#pragma once

#ifndef SPA_DESIGNENTITIESFACTORY_H
#define SPA_DESIGNENTITIESFACTORY_H

#include <iostream>

#include "DesignEntity.h"

using namespace std;

class DesignEntitiesFactory {
public:
    static DesignEntity* createDesignEntity(string designEntity, tuple<string, string> entityDetails);
};

#endif //SPA_DESIGNENTITIESFACTORY_H
