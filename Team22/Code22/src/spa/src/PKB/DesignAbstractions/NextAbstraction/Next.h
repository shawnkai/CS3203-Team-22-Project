//
// Created by Jai Lulla  on 8/3/23.
//

#pragma once

#ifndef SPA_NEXT_H
#define SPA_NEXT_H

#include <iostream>

#include "PKB/DesignAbstractions/DesignAbstraction.h"

using namespace std;

class Next: public DesignAbstraction {
public:
    explicit Next(tuple<string, string, string> abstractionDetails);

    string getTypeOfAbstraction() override;
};

#endif //SPA_NEXT_H
