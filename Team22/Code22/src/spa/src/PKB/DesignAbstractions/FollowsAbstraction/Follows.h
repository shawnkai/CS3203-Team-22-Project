//
// Created by Jai Lulla  on 16/2/23.
//

#pragma once

#ifndef SPA_FOLLOWS_H
#define SPA_FOLLOWS_H

#include <iostream>

#include "PKB/DesignAbstractions/DesignAbstraction.h"

using namespace std;

class Follows: public DesignAbstraction {
public:
    explicit Follows(tuple<string, string, string> abstractionDetails);

    string getTypeOfAbstraction() override;
};

#endif //SPA_FOLLOWS_H
