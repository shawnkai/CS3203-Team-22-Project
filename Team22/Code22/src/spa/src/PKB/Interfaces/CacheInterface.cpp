//
// Created by Jai Lulla  on 2/4/23.
//

#include <iostream>

#include "PKB/Cache/CacheManager.h"
#include "CacheInterface.h"

using namespace std;

void CacheInterface::addToCache(string accessKey, ResultTable *resultTable) {
    CacheManager::addToCache(accessKey, resultTable);
}

ResultTable *CacheInterface::getResultTableFromCache(string accessKey) {
    return CacheManager::getResultTableFromCache(accessKey);
}

unordered_map<string, ResultTable *> CacheInterface::getCacheDatabase() {
    return CacheManager::getCacheDatabase();
}

void CacheInterface::clearCache() {
    CacheManager::clearCache();
}
