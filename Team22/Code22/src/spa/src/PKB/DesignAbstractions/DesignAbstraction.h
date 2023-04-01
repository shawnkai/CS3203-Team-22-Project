//
// Created by Jai Lulla  on 2/2/23.
//

#pragma once

#ifndef SPA_DESIGNABSTRACTION_H
#define SPA_DESIGNABSTRACTION_H

#include <iostream>
#include <vector>

using namespace std;

class DesignAbstraction {
    string entityTypeBeingAbstracted; // entityType that is being referred to
    string entityName; // could be variable name (usually or stmt...)
    vector<string> entityOccurrences; // value to push in (stmtNo or procName...)

    virtual bool isOccurrencePresent(string entityOccurrence);

public:
    explicit DesignAbstraction(tuple<string, string, string> abstractionDetails);

    virtual void addAdditionalOccurrence(string entityOccurrence);
    virtual string getEntityTypeBeingAbstracted();
    virtual string getEntityName();
    virtual vector<string> getEntityOccurrence();

    virtual string getTypeOfAbstraction() = 0;

};

#endif //SPA_DESIGNABSTRACTION_H
