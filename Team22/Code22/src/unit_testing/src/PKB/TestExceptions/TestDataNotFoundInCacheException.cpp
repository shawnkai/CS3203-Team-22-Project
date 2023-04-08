//
// Created by Jai Lulla  on 30/3/23.
//

#include <iostream>

#include "catch.hpp"

#include "PKB/Cache/CacheDatabase.h"
#include "PKB/Exceptions/DataNotFoundInCacheException.cpp"

using namespace std;

TEST_CASE("Test 1: Catch DataNotFoundInCacheException") {
    bool exceptionThrown = false;

    try {
        CacheDatabase *cacheDatabase = new CacheDatabase;
        cacheDatabase->addToCache("Test", nullptr);

        cacheDatabase->getResultTableFromCache("INVALID");
    } catch (DataNotFoundInCacheException &e) {
        exceptionThrown = true;
    }

    REQUIRE(exceptionThrown);
}
