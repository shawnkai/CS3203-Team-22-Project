//
// Created by Jai Lulla  on 2/2/23.
//

#pragma once

#ifndef SPA_RESULT_H
#define SPA_RESULT_H

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class Result {
    string entityType;
    string entityName;
    vector<string> result;

public:
    explicit Result(string entityType, string entityName, vector<string> result);// inline giving error

    string toString();
    string getQueryEntityName();
    string getQueryEntityType();
    vector<string> getQueryResult();
    bool areEqual(Result otherResult);// For testing purposes
};

#endif//SPA_RESULT_H
