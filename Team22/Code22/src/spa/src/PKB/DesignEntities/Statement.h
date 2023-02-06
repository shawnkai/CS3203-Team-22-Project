//
// Created by Jai Lulla  on 5/2/23.
//

#pragma once

#ifndef SPA_STATEMENT_H
#define SPA_STATEMENT_H

#include <iostream>

#include "DesignEntity.h"

using namespace std;

class Statement: public DesignEntity {
public:
    explicit Statement(tuple<string, string> entityDetails);

    string getTypeOfEntity() override;
};

#endif //SPA_STATEMENT_H
