//
// Created by Jai Lulla  on 5/2/23.
//

#pragma once

#ifndef SPA_READMODIFIES_H
#define SPA_READMODIFIES_H

#include <iostream>

#include "Modifies.h"

using namespace std;

class ReadModifies : public Modifies {
public:
    explicit ReadModifies(tuple<string, string, string> abstractionDetails);

    string getTypeOfAbstraction() override;
};


#endif//SPA_READMODIFIES_H
