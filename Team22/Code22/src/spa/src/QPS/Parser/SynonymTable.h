//
// Created by Tanishq Sharma on 4/3/23.
//

#ifndef SPA_SYNONYMTABLE_H
#define SPA_SYNONYMTABLE_H

#include "QPS/Entities/Entities.h"
#include "QPS/Exceptions/Exceptions.h"

#include <map>
#include <vector>


class SynonymTable {
private:
    map<string, DesignEntity *> table;

public:
    vector<tuple<string, string>> getSimpleSynonymTable();

    bool exists(string name);

    void add(string type, const string &name);

    bool isEquivalentTo(const map<string, string> &expectedTable);

    DesignEntity *get(const string &name, const string &desiredType);
};


#endif//SPA_SYNONYMTABLE_H
