//
// Created by Jai Lulla  on 14/3/23.
//

#pragma once

#ifndef SPA_BLOCKTOSTATEMENTNUMBERS_H
#define SPA_BLOCKTOSTATEMENTNUMBERS_H

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class BlockToStatementNumbers {
    map<int, vector<int>> blockToStatementNumbersDatabase;

public:
    explicit BlockToStatementNumbers(map<int, vector<int>> blockToStatementNumbersDatabase);
    void addToDatabase(int blockNumber, vector<int> statementNumbers);
    map<int, vector<int>> getBlockToStatementNumbersDatabase();
    void copyBlockToStatementNumbersDatabase(map<int, vector<int>> blockToStatementNumbers);
    void clearDatabase();
};

#endif //SPA_BLOCKTOSTATEMENTNUMBERS_H
