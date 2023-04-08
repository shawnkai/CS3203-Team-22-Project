//
// Created by Atin Sakkeer Hussain on 08/04/2023.
//

#include "Optimizer.h"

int root(int node, unordered_map<int, int>& parent) {
    if (node == parent.at(node)) {
        return node;
    }

    // Otherwise, set topmost vertex of
    // its parent as its topmost vertex
    return parent[node] = root(parent[node], parent);
}

void connect(int a, int b, unordered_map<int, int>& parent)
{
    // Connect edges
    a = root(a, parent);
    b = root(b, parent);

    if (a != b) {
        parent[b] = a;
    }
}

vector<vector<Expression *>> QueryOptimizer::createGroups(const vector<Expression *>& conditions) {
    unordered_map<string, vector<int>> synMapping;
    unordered_map<Expression*, int> expMapping;

    unordered_map<int, int> parent;

    int ind = 1;
    for (Expression *exp : conditions) {
        expMapping.insert({exp, ind});
        for (const string& s : exp->getSynEntities()) {
            if (synMapping.find(s) == synMapping.end()) {
                synMapping.insert({s, {}});
            }
            synMapping.at(s).push_back(ind);
        }
        parent.insert({ind, ind});
        ind += 1;
    }


    vector<pair<int, int>> edges;

    for (auto kv : synMapping) {
        for (int i = 0; i < kv.second.size() - 1; i++) {
            edges.emplace_back(kv.second[i], kv.second[i+1]);
        }
    }

    for (auto kv : edges) {
        connect(kv.first, kv.second, parent);
    }

    unordered_map<int, vector<Expression*>> groups;

    for (auto kv : expMapping) {
        int r = root(parent[kv.second], parent);
        if (groups.find(r) == groups.end()) {
            groups.insert({r, {}});
        }
        groups.at(r).push_back(kv.first);
    }

    vector<vector<Expression*>> grouped;

    for (const auto& kv: groups) {
        grouped.push_back(kv.second);
    }

    return grouped;
}