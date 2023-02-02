//
// Created by Jai Lulla  on 2/2/23.
//

#include <iostream>

#include "Result.h"

using namespace std;

inline Result::Result(vector<string> result) {
    this->result = result;
}

string Result::toString() {
    string resultString = "";

    for (auto item: this->result) {
        resultString += (item + ", ");
    }

    return resultString;
}

vector<string> Result::getResult() {
    return this->result;
}