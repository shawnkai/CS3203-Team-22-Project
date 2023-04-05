//
// Created by Atin Sakkeer Hussain on 02/03/2023.
//

#include "ResultTable.h"

#include <utility>
#include <set>
#include <unordered_set>

ResultTable::ResultTable(initializer_list<pair<string, vector<string>>> args) {
    for (pair<string, vector<string>> p : args) {
        table.insert(p);
        this->columns.push_back(p.first);
    }
}

ResultTable::ResultTable(const unordered_map<string, vector<string>>& table) {
    this->table = table;
    for (const auto& kv : table) {
        this->columns.push_back(kv.first);
    }
}

ResultTable::ResultTable(const unordered_map<string, vector<string>> &table, vector<string> columns) {
    this->table = table;
    this->columns = std::move(columns);
}

bool ResultTable::equals(ResultTable* table2) {
    if (this->table.size() != table2->table.size()) {
        return false;
    }

    if (this->table.size() == 0 & table2->table.size() == 0) {
        return true;
    }

    unordered_set<string> key1;
    unordered_set<string> key2;

    for (const auto& kv: this->table) {
        key1.insert(kv.first);
    }
    for (const auto& kv: table2->table) {
        key2.insert(kv.first);
    }

    if (key1 != key2) {
        return false;
    }

    vector<vector<string>> t1;
    vector<vector<string>> t2;
    for (int i = 0; i < this->getSize(); i++) {
        vector<string> t1_temp;
        vector<string> t2_temp;
        for (const auto& k : key1) {
            t1_temp.push_back(this->table.find(k)->second[i]);
            t2_temp.push_back(table2->table.find(k)->second[i]);
        }
        t1.push_back(t1_temp);
        t2.push_back(t2_temp);
    }

    if (t1.size() != t2.size()) {
        return false;
    }

    for (const vector<string>& t1_temp : t1) {
        bool found = false;
        for (const vector<string>& t2_temp : t2) {
            if (t1_temp == t2_temp) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

string ResultTable::toString() {
    size_t length = this->getSize();
    string result;
    for (const auto& kv: this->table) {
        result.append(kv.first + "\t");
    }
    result.append("\n");
    for (int i = 0; i < length; i++) {
        for (auto kv : this->table) {
            if (i < kv.second.size()) {
                result.append(kv.second[i] + "\t");
            } else {
                result.append( "-\t");
            }
        }
        result.append("\n");
    }
    return result;
}

ResultTable* ResultTable::crossProduct(ResultTable* table2, const unordered_set<string>& all_keys) {
    unordered_map<string, vector<string>> result;
    for (const string& key: all_keys) {
        result.insert({key, {}});
    }

    for(int i = 0; i < this->getSize(); i++) {
        for (int j = 0; j < table2->getSize(); j++) {
            for (const auto& kv1 : this->table) {
                result.find(kv1.first)->second.push_back(kv1.second[i]);
            }
            for (const auto& kv2 : table2->table) {
                result.find(kv2.first)->second.push_back(kv2.second[j]);
            }
        }
    }
    return new ResultTable(result);
}

ResultTable* ResultTable::naturalJoin(ResultTable* table2, const unordered_set<string>& all_keys, unordered_set<string> common_keys) {
    vector<int> target_indexes;
   unordered_map<int, vector<int>> index_map;
    for (int i = 0; i < table2->getSize(); i ++) {
        target_indexes.push_back(i);
        index_map.insert({i, {}});
    }

   unordered_map<int, vector<int>> index_mapping;


    for (int i = 0; i < table2->getSize(); i++) {
        string key = *common_keys.begin();
        string target_v = table2->table.find(key)->second[i];
        vector<string> targets = this->table.find(key)->second;
        vector<int> indices;
        int ind = 0;
        for (const string& t : targets) {
            if (t == target_v) {
                bool matched = true;
                for (auto kv : this->table) {
                    if (common_keys.find(kv.first) != common_keys.end() && kv.second[ind] != table2->table.find(kv.first)->second[i]) {
                        matched = false;
                        break;
                    }
                }
                if (matched) {
                    index_map.find(i)->second.push_back(ind);
                }
            }
            ind += 1;
        }
    }

   unordered_map<string, vector<string>> result;
    for (const string& key: all_keys) {
        result.insert({key, {}});
    }

    vector<int> indices;
    vector<vector<int>> target_indices;

    for (const auto& ind_pair : index_map) {
        indices.push_back(ind_pair.first);
        target_indices.push_back(ind_pair.second);
    }

    for (const auto& ind_pair : index_map) {
        for (int i: ind_pair.second) {
            for (auto kv : table2->table) {
                result.find(kv.first)->second.push_back(kv.second[ind_pair.first]);
            }
            for (auto kv2: this->table) {
                if (common_keys.find(kv2.first) == common_keys.end()) {
                    result.find(kv2.first)->second.push_back(kv2.second[i]);
                }
            }
        }
    }

    return new ResultTable(result);
}

ResultTable* ResultTable::intersection(ResultTable* table2) {
    unordered_set<string> common_keys;
    unordered_set<string> all_keys;
    for (const auto& kv : this->table) {
        all_keys.insert(kv.first);
    }
    for (const auto& kv : table2->table) {
        if (this->table.find(kv.first) != this->table.end()) {
            common_keys.insert(kv.first);
            continue;
        }
        all_keys.insert(kv.first);
    }

    if (common_keys.empty()) {
        if (table2->getSize() == 0 || this->getSize() == 0) {
            return new BooleanFalseTable();
        } else {
            return this->crossProduct(table2, all_keys);
        }
    } else {
        return this->naturalJoin(table2, all_keys, common_keys);
    }
}

ResultTable* ResultTable::intersection(vector<ResultTable*> tables) {
    vector resultTables = vector(std::move(tables));

    ResultTable* finalResult = resultTables[0];

    for (int i = 1; i < resultTables.size(); i++) {
        finalResult = finalResult->intersection(resultTables[i]);
    }
    return finalResult;
}


ResultTable* ResultTable::getColumns(const vector<string>& columns) {
   unordered_map<string, vector<string>> mod;
    for (const string& column : columns) {
        if (!Utilities::checkIfPresent(this->getColumnNames(), column)) {
            continue;
        }
        mod.insert({column, this->getValues(column)});
    }
    return new ResultTable(mod, columns);
}

vector<string> ResultTable::getValues() {
    vector<vector<string>> columnValues;
    for (const string& column : this->columns) {
        columnValues.push_back(this->getValues(column));
    }
    vector<string> result;
    for (int i = 0; i < this->getSize(); i++) {
        string row;
        for (int j = 0; j < columns.size(); j++) {
            row += columnValues[j][i] + " ";
        }
        row.pop_back();
        result.push_back(row);
    }
    set<string> s(result.begin(), result.end());
    result.assign( s.begin(), s.end());
    return result;
}

vector<string> ResultTable::getValues(const string& column) {
    return this->table.find(column)->second;
}

vector<string> ResultTable::getColumnNames() {
    vector<string> columns;
    for (const auto& kv: this->table) {
        columns.push_back(kv.first);
    }
    return columns;
}

::size_t ResultTable::getSize() {
    if (this->table.empty()) {
        return 0;
    }
    return this->table.begin()->second.size();
}

void ResultTable::renameColumn(const string& oldName, const string& newName) {
    vector<string> data = this->table.find(oldName)->second;
    this->table.insert({newName, data});
    this->table.erase(this->table.find(oldName));
}

BooleanTrueTable::BooleanTrueTable() : ResultTable({{"_", {"-"}}}) {}

vector<string> BooleanTrueTable::getValues() {
    return {"TRUE"};
}

BooleanFalseTable::BooleanFalseTable() : ResultTable({{"_", {}}}) {}

vector<string> BooleanFalseTable::getValues() {
    return {"FALSE"};
}

