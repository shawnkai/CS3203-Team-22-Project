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
    vector<string> result;

public:
    inline explicit Result(vector<string> result);

    string toString();
    vector<string> getResult();
};

#endif //SPA_RESULT_H
