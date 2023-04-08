//
// Created by Jai Lulla  on 30/3/23.
//

#pragma once

#ifndef SPA_CACHEDATABASE_H
#define SPA_CACHEDATABASE_H

#include <iostream>
#include <unordered_map>

#include "QPS/Evaluator/ResultTable.h"

using namespace std;

class CacheDatabase {
    unordered_map<string, ResultTable *> cacheDatabase;

public:
    void addToCache(string accessKey, ResultTable *resultTable);
    ResultTable *getResultTableFromCache(string accessKey);
    unordered_map<string, ResultTable *> getCacheDatabase();
    void clearCache();
};

#endif//SPA_CACHEDATABASE_H
