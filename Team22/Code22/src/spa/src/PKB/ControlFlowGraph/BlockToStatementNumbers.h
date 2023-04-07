//
// Created by Jai Lulla  on 14/3/23.
//

#pragma once

#ifndef SPA_BLOCKTOSTATEMENTNUMBERS_H
#define SPA_BLOCKTOSTATEMENTNUMBERS_H

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class BlockToStatementNumbers {
    unordered_map<int, vector<int>> blockToStatementNumbersDatabase;

public:
    explicit BlockToStatementNumbers(unordered_map<int, vector<int>> blockToStatementNumbersDatabase);
    explicit BlockToStatementNumbers();

    void addToDatabase(int blockNumber, vector<int> statementNumbers);
    unordered_map<int, vector<int>> getBlockToStatementNumbersDatabase();
    void copyBlockToStatementNumbersDatabase(unordered_map<int, vector<int>> blockToStatementNumbers);
    void clearDatabase();
};

#endif//SPA_BLOCKTOSTATEMENTNUMBERS_H
