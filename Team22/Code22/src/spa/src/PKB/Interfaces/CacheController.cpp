//
// Created by Jai Lulla  on 2/4/23.
//

#include <iostream>

#include "PKB/Cache/CacheManager.h"
#include "CacheController.h"

using namespace std;

void CacheController::addToCache(string accessKey, ResultTable *resultTable) {
    CacheManager::addToCache(accessKey, resultTable);
}

ResultTable *CacheController::getResultTableFromCache(string accessKey) {
    return CacheManager::getResultTableFromCache(accessKey);
}

unordered_map<string, ResultTable *> CacheController::getCacheDatabase() {
    return CacheManager::getCacheDatabase();
}

void CacheController::clearCache() {
    CacheManager::clearCache();
}
