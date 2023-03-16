//
// Created by Jai Lulla  on 14/3/23.
//

#include <iostream>

#include "StatementNumberToBlock.h"

using namespace std;

StatementNumberToBlock::StatementNumberToBlock(map<int, int> statementNumbersToBlockDatabase) {
    this->statementNumbersToBlockDatabase = statementNumbersToBlockDatabase;
}

StatementNumberToBlock::StatementNumberToBlock() {
    this->statementNumbersToBlockDatabase = map<int, int> {};
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
    this->statementNumbersToBlockDatabase = map<int, int> {};
}
