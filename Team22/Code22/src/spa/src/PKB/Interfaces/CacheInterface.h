//
// Created by Jai Lulla  on 2/4/23.
//

#pragma once

#ifndef SPA_CACHEINTERFACE_H
#define SPA_CACHEINTERFACE_H

#include <iostream>
#include <unordered_map>

#include "QPS/Evaluator/ResultTable.h"

using namespace std;

class CacheInterface {
public:
    void addToCache(string accessKey, ResultTable *resultTable);
    ResultTable *getResultTableFromCache(string accessKey);
    unordered_map<string, ResultTable *> getCacheDatabase();
    void clearCache();
};

#endif//SPA_CACHEINTERFACE_H
