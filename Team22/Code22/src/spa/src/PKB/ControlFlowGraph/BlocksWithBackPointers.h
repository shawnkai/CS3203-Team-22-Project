//
// Created by Jai Lulla  on 14/3/23.
//

#pragma once

#ifndef SPA_BLOCKSWITHBACKPOINTERS_H
#define SPA_BLOCKSWITHBACKPOINTERS_H

#include <iostream>
#include <unordered_set>

using namespace std;

class BlocksWithBackPointers {
    unordered_set<int> blocksWithBackPointersDatabase;

public:
    explicit BlocksWithBackPointers(unordered_set<int> blocksWithBackPointersDatabase);
    explicit BlocksWithBackPointers();

    void addToDatabase(int blockWithBackPointer);
    void copyBlocksWithBackPointersDatabase(unordered_set<int> blocksWithBackPointers);
    unordered_set<int> getBlocksWithBackPointersDatabase();
    void clearDatabase();
};

#endif //SPA_BLOCKSWITHBACKPOINTERS_H
