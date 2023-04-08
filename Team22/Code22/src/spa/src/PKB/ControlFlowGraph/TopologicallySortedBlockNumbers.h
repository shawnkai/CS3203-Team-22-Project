//
// Created by Jai Lulla  on 14/3/23.
//

#pragma once

#ifndef SPA_TOPOLOGICALLYSORTEDBLOCKNUMBERS_H
#define SPA_TOPOLOGICALLYSORTEDBLOCKNUMBERS_H

#include <iostream>
#include <vector>

using namespace std;

class TopologicallySortedBlockNumbers {
    vector<int> topologicallySortedBlockNumbersDatabase;

public:
    explicit TopologicallySortedBlockNumbers(vector<int> topologicallySortedBlockNumbersDatabase);
    explicit TopologicallySortedBlockNumbers();

    void addBlockNumber(int blockNumber);
    void copyTopologicallySortedBlockNumbersDatabase(vector<int> topologicallySortedBlockNumbers);
    vector<int> getTopologicallySortedBlockNumbersDatabase();
    void clearDatabase();
};

#endif//SPA_TOPOLOGICALLYSORTEDBLOCKNUMBERS_H
