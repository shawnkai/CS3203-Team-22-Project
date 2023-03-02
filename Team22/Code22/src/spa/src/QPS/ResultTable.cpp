//
// Created by Atin Sakkeer Hussain on 02/03/2023.
//

#include "QPS/ResultTable.h"

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
        for (vector<string> t2_temp : t2) {
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
    int length = this->getSize();
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

ResultTable ResultTable::crossProduct(ResultTable table2, vector<string> all_keys) {
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

ResultTable ResultTable:: naturalJoin(ResultTable table2, vector<string> all_keys, vector<string> common_keys) {
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

//    for (const auto& key : common_keys) {
//        int ind = 0;
//        vector<string> target = this->table.find(key)->second;
//        for (const auto& values : table2.table.find(key)->second) {
//            if (!Utilities::checkIfPresent(target, values)) {
//                target_indexes.erase(std::remove(target_indexes.begin(), target_indexes.end(), ind), target_indexes.end());
//            } else {
//                for (int i = 0; i < target.size(); i++) {
//                    if (target[i] == values) {
//                        index_map.find(ind)->second.push_back(i);
//                    }
//                }
//            }
//            ind += 1;
//        }
//    }

    ::printf("Mapping: \n");
    for (auto kv: index_map) {
        ::printf("Target Index: %d, Indexes: ", kv.first);
        for (int i : kv.second) {
            ::printf("%d, ", i);
        }
        ::printf("\n");
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
        }
        all_keys.push_back(kv.first);
    }

    if (common_keys.empty()) {
        if (table2.getSize() == 0) {
            return *this;
        } else if (this->getSize() == 0) {
            return table2;
        } else {
            return this->crossProduct(table2, all_keys);
        }
    } else {
        return this->naturalJoin(table2, all_keys, common_keys);
    }

//    ::printf("Mapping: \n");
//    for (auto kv: index_map) {
//        ::printf("Target Index: %d, Indexes: ", kv.first);
//        for (int i : kv.second) {
//            ::printf("%d, ", i);
//        }
//        ::printf("\n");
//    }

}

ResultTable ResultTable::intersection(initializer_list<ResultTable> tables) {
    vector resultTables = vector(tables);

    ResultTable finalResult = resultTables[0];

    for (int i = 1; i < resultTables.size(); i++) {
        finalResult = finalResult.intersection(resultTables[i]);
    }

    return finalResult;
}


//int main() {
//    IntermediateResultTable table1({make_pair<string, vector<string>>("s", {"1", "2", "3", "4", "5"}),
//                       make_pair<string, vector<string>>("s1", {"6", "7", "8", "9", "10"})});
//
//    IntermediateResultTable table2({make_pair<string, vector<string>>("s", {"2", "4", "4"}),
//                       make_pair<string, vector<string>>("v", {"x", "x", "y"})});
//
//    ::printf("%s\n", table1.toString().c_str());
//}