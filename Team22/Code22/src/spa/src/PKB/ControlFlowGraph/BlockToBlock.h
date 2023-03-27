//
// Created by Jai Lulla  on 14/3/23.
//

#pragma once

#ifndef SPA_BLOCKTOBLOCK_H
#define SPA_BLOCKTOBLOCK_H

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class BlockToBlock {
    map<int, vector<int>> blockToBlockDatabase;

public:
    explicit BlockToBlock(map<int, vector<int>> blockToBlockDatabase);
    explicit BlockToBlock();

    void addToDatabase(int block, vector<int> nextBlock);
    map<int, vector<int>> getBlockToBlockDatabase();
    void copyBlockToBlockDatabase(map<int, vector<int>> blockToBlock);
    void clearDatabase();
};

#endif //SPA_BLOCKTOBLOCK_H
