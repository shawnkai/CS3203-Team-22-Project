//
// Created by Jai Lulla  on 14/3/23.
//

#include <iostream>

#include "BlockToBlock.h"

using namespace std;

BlockToBlock::BlockToBlock(map<int, int> blockToBlockDatabase) {
    this->blockToBlockDatabase = blockToBlockDatabase;
}

void BlockToBlock::addToDatabase(int block, int nextBlock) {
    this->blockToBlockDatabase.insert(make_pair(block, nextBlock));
}

void BlockToBlock::copyBlockToBlockDatabase(map<int, int> blockToBlock) {
    this->blockToBlockDatabase = blockToBlock;
}

map<int, int> BlockToBlock::getBlockToBlockDatabase() {
    return this->blockToBlockDatabase;
}

void BlockToBlock::clearDatabase() {
    std::destroy(this->blockToBlockDatabase.begin(), this->blockToBlockDatabase.end());
}
