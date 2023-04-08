//
// Created by Jai Lulla  on 14/2/23.
//

#pragma once

#ifndef SPA_PRINTUSES_H
#define SPA_PRINTUSES_H

#include <iostream>

#include "Uses.h"

using namespace std;

class PrintUses : public Uses {
public:
    explicit PrintUses(tuple<string, string, string> abstractionDetails);

    string getTypeOfAbstraction() override;
};

#endif//SPA_PRINTUSES_H
