//
// Created by Jai Lulla  on 30/3/23.
//

#include <iostream>

#include "CacheManager.h"

using namespace std;

void CacheManager::addToCache(string accessKey, ResultTable *resultTable) {
    cacheDatabase->addToCache(accessKey, resultTable);
}

ResultTable *CacheManager::getResultTableFromCache(string accessKey) {
    return cacheDatabase->getResultTableFromCache(accessKey);
}

unordered_map<string, ResultTable*> CacheManager::getCacheDatabase() {
    return cacheDatabase->getCacheDatabase();
}

void CacheManager::clearCache() {
    cacheDatabase->clearCache();
}
