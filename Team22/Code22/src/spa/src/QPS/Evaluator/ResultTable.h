//
// Created by Atin Sakkeer Hussain on 02/03/2023.
//

#ifndef SPA_RESULTTABLE_H
#define SPA_RESULTTABLE_H

#include <map>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "Utilities.h"

using namespace std;


class ResultTable {
    vector<string> columns;
    unordered_map<string, vector<string>> table;

public:
    ResultTable(initializer_list<pair<string, vector<string>>> args);

    explicit ResultTable(const unordered_map<string, vector<string>>& table);
    explicit ResultTable(const unordered_map<string, vector<string>>& table, vector<string> columns);

    ::size_t getSize();

    ResultTable* intersection(ResultTable* table2);

    static ResultTable* intersection(vector<ResultTable*> resultTables);

    ResultTable* removeColumn(string column) {
        auto it = this->table.find(column);
        if (it != this->table.end()) {
            this->table.erase(it);
        }
        return new ResultTable(this->table);
    }

    string toString();

    ResultTable* getColumns(const vector<string>& columns);

    virtual vector<string> getValues();

    vector<string> getValues(const string& column);

    vector<string> getColumnNames();

    void renameColumn(const string& oldName, const string& newName);

    bool equals(ResultTable* table2);

private:

    ResultTable* crossProduct(ResultTable* table2, const unordered_set<string>& all_keys);

    ResultTable* naturalJoin(ResultTable* table2, const unordered_set<string>& all_keys, unordered_set<string> common_keys);

};

class BooleanTrueTable : public ResultTable {
public:
    BooleanTrueTable();

    vector<string> getValues();
};

class BooleanFalseTable : public ResultTable {
public:
    BooleanFalseTable();

    vector<string> getValues();
};

#endif //SPA_RESULTTABLE_H
