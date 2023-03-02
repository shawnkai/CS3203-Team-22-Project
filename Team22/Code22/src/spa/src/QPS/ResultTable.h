//
// Created by Atin Sakkeer Hussain on 02/03/2023.
//

#ifndef SPA_RESULTTABLE_H
#define SPA_RESULTTABLE_H

#include <map>
#include <string>
#include <vector>
#include "Utilities.h"

using namespace std;


class ResultTable {
    map<string, vector<string>> table;

public:
    ResultTable(initializer_list<pair<string, vector<string>>> args);

    explicit ResultTable(const map<string, vector<string>>& table);

    ::size_t getSize();

    ResultTable intersection(ResultTable table2);

    static ResultTable intersection(vector<ResultTable> resultTables);

    string toString();

    ResultTable getColumn(string column);

    vector<string> getValues(const string& column);

    vector<string> getColumnNames();

    bool equals(ResultTable table2);

private:

    ResultTable crossProduct(ResultTable table2, const vector<string>& all_keys);

    ResultTable naturalJoin(ResultTable table2, const vector<string>& all_keys, vector<string> common_keys);

};

class IntermediateResultTable : public ResultTable {
public:
    IntermediateResultTable(initializer_list<pair<string, vector<string>>> args);


};

class FinalResultTable : public ResultTable {
    //FinalResultTable();

    //static IntermediateResultTable intersection(IntermediateResultTable table1, IntermediateResultTable table2);
};

#endif //SPA_RESULTTABLE_H
