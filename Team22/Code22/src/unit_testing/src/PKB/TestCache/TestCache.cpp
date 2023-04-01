//
// Created by Jai Lulla  on 30/3/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/Interfaces/CacheController.h"

#include "PKB/Exceptions/DataNotFoundInCacheException.cpp"

using namespace std;

TEST_CASE("Test 1: Addition Of Data To Cache") {
    bool anyExceptionThrown = false;

    try {
        ResultTable resultTable = ResultTable(map<string, vector<string>> {});

        CacheController cacheController = CacheController();
        cacheController.addToCache("AccessKey_1", &resultTable);
    } catch (exception& e) {
        anyExceptionThrown = true;
    }

    REQUIRE(!anyExceptionThrown);
}

TEST_CASE("Test 2: Retrieval Of Data From Cache When Single Result Table is Stored") {
    ResultTable* resultTable = new ResultTable(
            map<string, vector<string>> {
                make_pair("sample", vector<string> {"sample"})
            });

    CacheController cacheController = CacheController();
    cacheController.addToCache("AccessKey_2", resultTable);
    ResultTable* result = cacheController.getResultTableFromCache("AccessKey_2");

    REQUIRE(result->equals(*resultTable));
}

TEST_CASE("Test 3: Retrieval Of Data From Cache When Multiple Result Tables are Stored") {
    ResultTable* resultTableOne = new ResultTable(
            map<string, vector<string>> {
                    make_pair("sample1", vector<string> {"sample1"})
            });

    ResultTable* resultTableTwo = new ResultTable(
            map<string, vector<string>> {
                    make_pair("sample2", vector<string> {"sample2"})
            });

    CacheController cacheController = CacheController();
    cacheController.addToCache("AccessKey_3", resultTableOne);
    cacheController.addToCache("AccessKey_4", resultTableTwo);

    ResultTable* resultOne = cacheController.getResultTableFromCache("AccessKey_3");
    ResultTable* resultTwo = cacheController.getResultTableFromCache("AccessKey_4");

    REQUIRE(((resultOne->equals(*resultTableOne)) && (resultTwo->equals(*resultTableTwo))));
}

TEST_CASE("Test 4: Retrieval Of Data From Cache Which Does Not Exist") {
    bool exceptionThrown = false;

    ResultTable* resultTable = new ResultTable(
            map<string, vector<string>> {
                    make_pair("sample", vector<string> {"sample"})
            });

    CacheController cacheController = CacheController();
    cacheController.addToCache("AccessKey_5", resultTable);

    try {
        ResultTable *resultOne = cacheController.getResultTableFromCache("InvalidAccessKey");
    } catch (DataNotFoundInCacheException& e) {
        exceptionThrown = true;
    }

    REQUIRE(exceptionThrown);
}

TEST_CASE("Test 5: Retrieval Of Cache Database") {
    ResultTable* resultTable = new ResultTable(
            map<string, vector<string>> {
                    make_pair("sample1", vector<string> {"sample1"})
            });

    CacheController cacheController = CacheController();
    cacheController.addToCache("AccessKey_6", resultTable);

    unordered_map<string, ResultTable*> db = cacheController.getCacheDatabase();
    ResultTable* result = db.find("AccessKey_6")->second;

    REQUIRE(result->equals(*resultTable));
}

TEST_CASE("Test 6: Test clearCacheAPI()") {
    ResultTable* resultTableOne = new ResultTable(
            map<string, vector<string>> {
                    make_pair("sample1", vector<string> {"sample1"})
            });

    ResultTable* resultTableTwo = new ResultTable(
            map<string, vector<string>> {
                    make_pair("sample2", vector<string> {"sample2"})
            });

    CacheController cacheController = CacheController();
    cacheController.addToCache("AccessKey_7", resultTableOne);
    cacheController.addToCache("AccessKey_8", resultTableTwo);

    ResultTable* resultOne = cacheController.getResultTableFromCache("AccessKey_7");
    ResultTable* resultTwo = cacheController.getResultTableFromCache("AccessKey_8");

    bool obtainedCorrectDatabaseBeforeClearing = ((resultOne->equals(*resultTableOne)) && (resultTwo->equals(*resultTableTwo)));

    cacheController.clearCache();

    unordered_map<string, ResultTable*> db = cacheController.getCacheDatabase();

    REQUIRE(((db.size() == 0) && (obtainedCorrectDatabaseBeforeClearing)));
}
