//
// Created by Jai Lulla  on 2/2/23.
//

#include <iostream>

#include "Result.h"

using namespace std;

Result::Result(string entityType, string entityName, vector<string> result) {
    this->entityType = entityType;
    this->entityName = entityName;
    this->result = result;
}

string Result::toString() {
    string resultString = (this->entityType) + ": " + (this->entityName) + ": ";

    for (auto item: this->result) {
        resultString += (item + ", ");
    }

    return resultString;
}

string Result::getQueryEntityName() {
    return this->entityName;
}

string Result::getQueryEntityType() {
    return this->entityType;
}

vector<string> Result::getQueryResult() {
    return this->result;
}