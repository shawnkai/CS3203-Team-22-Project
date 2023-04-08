//
// Created by Jai Lulla  on 4/2/23.
//

#pragma once

#ifndef SPA_PROCEDURE_H
#define SPA_PROCEDURE_H

#include <iostream>

#include "DesignEntity.h"

class Procedure : public DesignEntity {
public:
    explicit Procedure(tuple<string, string> entityDetails);

    string getTypeOfEntity() override;
};

#endif//SPA_PROCEDURE_H
