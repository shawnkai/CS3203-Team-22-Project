//
// Created by Jai Lulla  on 14/3/23.
//

#include <iostream>

#include "BlockToStatementNumbers.h"

using namespace std;

BlockToStatementNumbers::BlockToStatementNumbers(
        unordered_map<int, vector<int>> blockToStatementNumbersDatabase) {
    this->blockToStatementNumbersDatabase = blockToStatementNumbersDatabase;
}

BlockToStatementNumbers::BlockToStatementNumbers() {
    this->blockToStatementNumbersDatabase = unordered_map<int, vector<int>>{};
}

void BlockToStatementNumbers::addToDatabase(int blockNumber, vector<int> statementNumbers) {
    this->blockToStatementNumbersDatabase.insert(make_pair(blockNumber, statementNumbers));
}

unordered_map<int, vector<int>> BlockToStatementNumbers::getBlockToStatementNumbersDatabase() {
    return this->blockToStatementNumbersDatabase;
}

void BlockToStatementNumbers::copyBlockToStatementNumbersDatabase(unordered_map<int,
                                                                                vector<int>>
                                                                          blockToStatementNumbers) {
    this->blockToStatementNumbersDatabase = blockToStatementNumbers;
}

void BlockToStatementNumbers::clearDatabase() {
    this->blockToStatementNumbersDatabase = unordered_map<int, vector<int>>{};
}
