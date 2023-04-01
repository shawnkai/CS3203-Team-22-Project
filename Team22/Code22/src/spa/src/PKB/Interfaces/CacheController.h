//
// Created by Jai Lulla  on 2/4/23.
//

#pragma once

#ifndef SPA_CACHECONTROLLER_H
#define SPA_CACHECONTROLLER_H

#include <iostream>
#include <unordered_map>

#include "QPS/Evaluator/ResultTable.h"

using namespace std;

class CacheController {
public:
    void addToCache(string accessKey, ResultTable* resultTable);
    ResultTable* getResultTableFromCache(string accessKey);
    unordered_map<string, ResultTable*> getCacheDatabase();
    void clearCache();
};

#endif //SPA_CACHECONTROLLER_H
