//
// Created by Jai Lulla  on 30/3/23.
//

#include <iostream>


#include "CacheDatabase.h"

#include "PKB/Exceptions/DataNotFoundInCacheException.cpp"

using namespace std;

void CacheDatabase::addToCache(string accessKey, ResultTable *resultTable) {
    this->cacheDatabase.insert(make_pair(accessKey, resultTable));
}

ResultTable *CacheDatabase::getResultTableFromCache(string accessKey) {
    if (this->cacheDatabase.find(accessKey) != this->cacheDatabase.end()) {
        return this->cacheDatabase.find(accessKey)->second;
    }

    throw DataNotFoundInCacheException(("Result Table For" + accessKey + " Could Not Be Found in Cache").data());
}

unordered_map<string, ResultTable*> CacheDatabase::getCacheDatabase() {
    return this->cacheDatabase;
}

void CacheDatabase::clearCache() {
//    this->cacheDatabase = unordered_map<string, ResultTable*> {};
    this->cacheDatabase.clear();
}
