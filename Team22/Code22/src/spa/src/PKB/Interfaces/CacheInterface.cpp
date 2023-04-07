//
// Created by Jai Lulla  on 2/4/23.
//

#include <iostream>

#include "PKB/Cache/CacheManager.h"
#include "CacheInterface.h"

using namespace std;

void CacheInterface::addToCache(string accessKey, ResultTable *resultTable) {
    CacheDatabase* db = CacheManager::getCacheDatabase();
    db->addToCache(accessKey, resultTable);
}

ResultTable *CacheInterface::getResultTableFromCache(string accessKey) {
    CacheDatabase* db = CacheManager::getCacheDatabase();
    return db->getResultTableFromCache(accessKey);
}

unordered_map<string, ResultTable *> CacheInterface::getCacheDatabase() {
    CacheDatabase* db = CacheManager::getCacheDatabase();
    return db->getCacheDatabase();
}

void CacheInterface::clearCache() {
    CacheManager::clearCache();
}
