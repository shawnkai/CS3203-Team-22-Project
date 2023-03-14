//
// Created by Jai Lulla  on 14/3/23.
//

#include <iostream>

#include "StatementNumberToBlock.h"

using namespace std;

StatementNumberToBlock::StatementNumberToBlock(map<int, int> statementNumbersToBlockDatabase) {
    this->statementNumbersToBlockDatabase = statementNumbersToBlockDatabase;
}

void StatementNumberToBlock::addToDatabase(int statementNumber, int block) {
    this->statementNumbersToBlockDatabase.insert(make_pair(statementNumber, block));
}

map<int, int> StatementNumberToBlock::getStatementNumbersToBlockDatabase() {
    return this->statementNumbersToBlockDatabase;
}

void StatementNumberToBlock::copyStatementNumberToBlockDatabase(map<int, int> statementNumberToBlock) {
    this->statementNumbersToBlockDatabase = statementNumberToBlock;
}

void StatementNumberToBlock::clearDatabase() {
    std::destroy(this->statementNumbersToBlockDatabase.begin(), this->statementNumbersToBlockDatabase.end());
}
