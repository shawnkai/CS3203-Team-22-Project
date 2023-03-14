//
// Created by Jai Lulla  on 14/3/23.
//

#pragma once

#ifndef SPA_BLOCKTOBLOCK_H
#define SPA_BLOCKTOBLOCK_H

#include <iostream>
#include <map>

using namespace std;

class BlockToBlock {
    map<int, int> blockToBlockDatabase;

public:
    explicit BlockToBlock(map<int, int> blockToBlockDatabase);
    void addToDatabase(int block, int nextBlock);
    map<int, int> getBlockToBlockDatabase();
    void copyBlockToBlockDatabase(map<int, int> blockToBlock);
    void clearDatabase();
};

#endif //SPA_BLOCKTOBLOCK_H
