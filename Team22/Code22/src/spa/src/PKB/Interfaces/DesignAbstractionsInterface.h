//
// Created by Jai Lulla  on 30/3/23.
//

#pragma once

#ifndef SPA_DESIGNABSTRACTIONSINTERFACE_H
#define SPA_DESIGNABSTRACTIONSINTERFACE_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>

#include "Result.h"

using namespace std;

class DesignAbstractionsInterface {
public:
    void addDesignAbstraction(string designAbstraction, tuple<string, string, string> abstractionDetails);
    Result getDesignAbstraction(string abstractionType, tuple<string, string> query);
    // Overloaded APIs, for all except modifies and uses
    void addDesignAbstraction(string designAbstraction, tuple<string, string> abstractionDetails);
    Result getDesignAbstraction(string abstractionType, string query);
    vector<Result> getAllDesignAbstractions(string designAbstractionType, string entityTypeBeingAbstracted);
    unordered_map<string, unordered_set<string>> getAllVariablesCapturedByDesignAbstraction(
            string designAbstractionType, string entityTypeBeingAbstracted);
};

#endif//SPA_DESIGNABSTRACTIONSINTERFACE_H
