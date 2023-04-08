//
// Created by Jai Lulla  on 14/3/23.
//

#include <iostream>

#include "BlockToBlock.h"

using namespace std;

BlockToBlock::BlockToBlock(unordered_map<int, vector<int>> blockToBlockDatabase) {
    this->blockToBlockDatabase = blockToBlockDatabase;
}

BlockToBlock::BlockToBlock() {
    this->blockToBlockDatabase = unordered_map<int, vector<int>>{};
}

void BlockToBlock::addToDatabase(int block, vector<int> nextBlock) {
    this->blockToBlockDatabase.insert(make_pair(block, nextBlock));
}

void BlockToBlock::copyBlockToBlockDatabase(unordered_map<int, vector<int>> blockToBlock) {
    this->blockToBlockDatabase = blockToBlock;
}

unordered_map<int, vector<int>> BlockToBlock::getBlockToBlockDatabase() {
    return this->blockToBlockDatabase;
}

void BlockToBlock::clearDatabase() {
    this->blockToBlockDatabase = unordered_map<int, vector<int>>{};
}
