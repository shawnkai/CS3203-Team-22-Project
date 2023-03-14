//
// Created by Jai Lulla  on 14/3/23.
//

#pragma once

#ifndef SPA_STATEMENTNUMBERTOBLOCK_H
#define SPA_STATEMENTNUMBERTOBLOCK_H

#include <iostream>
#include <map>

using namespace std;

class StatementNumberToBlock {
    map<int, int> statementNumbersToBlockDatabase;

public:
    explicit StatementNumberToBlock(map<int, int> statementNumbersToBlockDatabase);
    void addToDatabase(int statementNumber, int block);
    map<int, int> getStatementNumbersToBlockDatabase();
    void copyStatementNumberToBlockDatabase(map<int, int> statementNumberToBlock);
    void clearDatabase();
};

#endif //SPA_STATEMENTNUMBERTOBLOCK_H
