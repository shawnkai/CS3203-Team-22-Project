//
// Created by Jai Lulla  on 16/2/23.
//

#pragma once

#ifndef SPA_FOLLOWSSTAR_H
#define SPA_FOLLOWSSTAR_H

#include <iostream>


#include "PKB/DesignAbstractions/DesignAbstraction.h"
using namespace std;

class FollowsStar: public DesignAbstraction {
public:
    explicit FollowsStar(tuple<string, string, string> abstractionDetails);

    string getTypeOfAbstraction() override;
};

#endif //SPA_FOLLOWSSTAR_H
