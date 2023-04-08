//
// Created by Jai Lulla  on 30/3/23.
//

#include <iostream>

#include "CacheManager.h"

using namespace std;

CacheDatabase *CacheManager::getCacheDatabase() {
    return cacheDatabase;
}

void CacheManager::clearCache() {
    cacheDatabase->clearCache();
}
