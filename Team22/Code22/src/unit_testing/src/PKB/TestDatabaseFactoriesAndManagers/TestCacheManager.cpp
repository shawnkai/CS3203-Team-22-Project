//
// Created by Jai Lulla  on 5/4/23.
//

#include <iostream>

#include "catch.hpp"

#include "PKB/Cache/CacheManager.h"

using namespace std;

TEST_CASE("Test 1: Get Cache Database") {
    CacheDatabase* db = CacheManager::getCacheDatabase();

    CacheDatabase* cdb = dynamic_cast<CacheDatabase*>(db);

    REQUIRE (cdb != nullptr);
}
