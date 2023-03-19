//
// Created by Jai Lulla  on 14/3/23.
//

#include <iostream>

#include "TopologicallySortedBlockNumbers.h"

using namespace std;

TopologicallySortedBlockNumbers::TopologicallySortedBlockNumbers(vector<int> topologicallySortedBlockNumbersDatabase) {
    this->topologicallySortedBlockNumbersDatabase = topologicallySortedBlockNumbersDatabase;
}

TopologicallySortedBlockNumbers::TopologicallySortedBlockNumbers() {
    this->topologicallySortedBlockNumbersDatabase = vector<int> {};
}

void TopologicallySortedBlockNumbers::addBlockNumber(int blockNumber) {
    this->topologicallySortedBlockNumbersDatabase.push_back(blockNumber);
}

void TopologicallySortedBlockNumbers::copyTopologicallySortedBlockNumbersDatabase(vector<int> topologicallySortedBlockNumbers) {
    this->topologicallySortedBlockNumbersDatabase = topologicallySortedBlockNumbers;
}

vector<int> TopologicallySortedBlockNumbers::getTopologicallySortedBlockNumbersDatabase() {
    return this->topologicallySortedBlockNumbersDatabase;
}

void TopologicallySortedBlockNumbers::clearDatabase() {
    this->topologicallySortedBlockNumbersDatabase = vector<int> {};
}
