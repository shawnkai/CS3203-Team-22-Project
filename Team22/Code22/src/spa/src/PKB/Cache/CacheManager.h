//
// Created by Jai Lulla  on 30/3/23.
//

#pragma once

#ifndef SPA_CACHEMANAGER_H
#define SPA_CACHEMANAGER_H

#include <iostream>

#include "PKB/Cache/CacheDatabase.h"

using namespace std;

class CacheManager {
    static inline CacheDatabase* cacheDatabase = new CacheDatabase;

public:
    static void addToCache(string accessKey, ResultTable *resultTable);
    static ResultTable* getResultTableFromCache(string accessKey);
    static unordered_map<string, ResultTable*> getCacheDatabase();
    static void clearCache();
};

#endif //SPA_CACHEMANAGER_H
