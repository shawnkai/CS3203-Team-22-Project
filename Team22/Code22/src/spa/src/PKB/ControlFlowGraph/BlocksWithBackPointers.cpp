//
// Created by Jai Lulla  on 14/3/23.
//

#include <iostream>

#include "BlocksWithBackPointers.h"

using namespace std;

BlocksWithBackPointers::BlocksWithBackPointers(unordered_set<int> blocksWithBackPointersDatabase) {
    this->blocksWithBackPointersDatabase = blocksWithBackPointersDatabase;
}

BlocksWithBackPointers::BlocksWithBackPointers() {
    this->blocksWithBackPointersDatabase = unordered_set<int> {};
}

void BlocksWithBackPointers::addToDatabase(int blockWithBackPointer) {
    this->blocksWithBackPointersDatabase.insert(blockWithBackPointer);
}

void BlocksWithBackPointers::copyBlocksWithBackPointersDatabase(unordered_set<int> blocksWithBackPointers) {
    this->blocksWithBackPointersDatabase = blocksWithBackPointers;
}

unordered_set<int> BlocksWithBackPointers::getBlocksWithBackPointersDatabase() {
    return this->blocksWithBackPointersDatabase;
}

void BlocksWithBackPointers::clearDatabase() {
    this->blocksWithBackPointersDatabase = unordered_set<int> {};
}
