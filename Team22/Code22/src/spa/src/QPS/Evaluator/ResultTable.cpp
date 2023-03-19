//
// Created by Atin Sakkeer Hussain on 02/03/2023.
//

#include "ResultTable.h"

#include <utility>
#include <set>

ResultTable::ResultTable(initializer_list<pair<string, vector<string>>> args) {
    for (pair<string, vector<string>> p : args) {
        table.insert(p);
    }
}

IntermediateResultTable::IntermediateResultTable(initializer_list<pair<string, vector<string>>> args) : ResultTable(args) {}

ResultTable::ResultTable(const map<string, vector<string>>& table) {
    this->table = table;
}

bool ResultTable::equals(ResultTable table2) {
    if (this->table.size() != table2.table.size()) {
        return false;
    }

    if (this->table.size() == 0 & table2.table.size() == 0) {
        return true;
    }

    vector<string> key1;
    vector<string> key2;

    for (const auto& kv: this->table) {
        key1.push_back(kv.first);
    }
    for (const auto& kv: table2.table) {
        key2.push_back(kv.first);
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
            t2_temp.push_back(table2.table.find(k)->second[i]);
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

ResultTable ResultTable::crossProduct(ResultTable table2, const vector<string>& all_keys) {
    map<string, vector<string>> result;
    for (const string& key: all_keys) {
        result.insert({key, {}});
    }

    for(int i = 0; i < this->getSize(); i++) {
        for (int j = 0; j < table2.getSize(); j++) {
            for (const auto& kv1 : this->table) {
                result.find(kv1.first)->second.push_back(kv1.second[i]);
            }
            for (const auto& kv2 : table2.table) {
                result.find(kv2.first)->second.push_back(kv2.second[j]);
            }
        }
    }
    return ResultTable(result);
}

ResultTable ResultTable:: naturalJoin(ResultTable table2, const vector<string>& all_keys, vector<string> common_keys) {
    vector<int> target_indexes;
    map<int, vector<int>> index_map;
    for (int i = 0; i < table2.getSize(); i ++) {
        target_indexes.push_back(i);
        index_map.insert({i, {}});
    }

    map<int, vector<int>> index_mapping;

    for (int i = 0; i < table2.getSize(); i++) {
        string key = common_keys[0];
        string target_v = table2.table.find(key)->second[i];
        vector<string> targets = this->table.find(key)->second;
        vector<int> indices;
        int ind = 0;
        for (const string& t : targets) {
            if (t == target_v) {
                bool matched = true;
                for (auto kv : this->table) {
                    if (Utilities::checkIfPresent(common_keys, kv.first) && kv.second[ind] != table2.table.find(kv.first)->second[i]) {
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

    map<string, vector<string>> result;
    for (const string& key: all_keys) {
        result.insert({key, {}});
    }

    for (const auto& ind_pair : index_map) {
        for (int i: ind_pair.second) {
            for (auto kv : table2.table) {
                result.find(kv.first)->second.push_back(kv.second[ind_pair.first]);
            }
            for (auto kv2: this->table) {
                if (!Utilities::checkIfPresent(common_keys, kv2.first)) {
                    result.find(kv2.first)->second.push_back(kv2.second[i]);
                }
            }
        }
    }

    return ResultTable(result);
}

ResultTable ResultTable::intersection(ResultTable table2) {
    vector<string> common_keys;
    vector<string> all_keys;
    for (const auto& kv : this->table) {
        all_keys.push_back(kv.first);
    }
    for (const auto& kv : table2.table) {
        if (this->table.find(kv.first) != this->table.end()) {
            common_keys.push_back(kv.first);
            continue;
        }
        all_keys.push_back(kv.first);
    }

    if (common_keys.empty()) {
        if (table2.getSize() == 0 || this->getSize() == 0) {
            map<string, vector<string>> empty_keys;
            for (const string& k : all_keys) {
                empty_keys.insert({k, {}});
            }
            return ResultTable(empty_keys);
        } else {
            return this->crossProduct(table2, all_keys);
        }
    } else {
        return this->naturalJoin(table2, all_keys, common_keys);
    }
}

ResultTable ResultTable::intersection(vector<ResultTable> tables) {
    vector resultTables = vector(std::move(tables));

    ResultTable finalResult = resultTables[0];

    for (int i = 1; i < resultTables.size(); i++) {
        finalResult = finalResult.intersection(resultTables[i]);
    }

    return finalResult;
}


ResultTable ResultTable::getColumn(string column) {
    if (!Utilities::checkIfPresent(this->getColumnNames(), column)) {
        return {};
    }
    vector<string> temp = this->getValues(column);
    set<string> s(temp.begin(), temp.end());
    temp.assign( s.begin(), s.end());
    return ResultTable({{column, temp}});
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