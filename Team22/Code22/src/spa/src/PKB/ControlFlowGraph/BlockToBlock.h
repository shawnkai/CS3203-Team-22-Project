//
// Created by Jai Lulla  on 14/3/23.
//

#pragma once

#ifndef SPA_BLOCKTOBLOCK_H
#define SPA_BLOCKTOBLOCK_H

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class BlockToBlock {
    unordered_map<int, vector<int>> blockToBlockDatabase;

public:
    explicit BlockToBlock(unordered_map<int, vector<int>> blockToBlockDatabase);
    explicit BlockToBlock();

    void addToDatabase(int block, vector<int> nextBlock);
    unordered_map<int, vector<int>> getBlockToBlockDatabase();
    void copyBlockToBlockDatabase(unordered_map<int, vector<int>> blockToBlock);
    void clearDatabase();
};

#endif//SPA_BLOCKTOBLOCK_H
