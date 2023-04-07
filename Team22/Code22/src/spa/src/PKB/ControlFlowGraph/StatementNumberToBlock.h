//
// Created by Jai Lulla  on 14/3/23.
//

#pragma once

#ifndef SPA_STATEMENTNUMBERTOBLOCK_H
#define SPA_STATEMENTNUMBERTOBLOCK_H

#include <iostream>
#include <unordered_map>

using namespace std;

class StatementNumberToBlock {
    unordered_map<int, int> statementNumbersToBlockDatabase;

public:
    explicit StatementNumberToBlock(unordered_map<int, int> statementNumbersToBlockDatabase);
    explicit StatementNumberToBlock();

    void addToDatabase(int statementNumber, int block);
    unordered_map<int, int> getStatementNumbersToBlockDatabase();
    void copyStatementNumberToBlockDatabase(unordered_map<int, int> statementNumberToBlock);
    void clearDatabase();
};

#endif //SPA_STATEMENTNUMBERTOBLOCK_H
