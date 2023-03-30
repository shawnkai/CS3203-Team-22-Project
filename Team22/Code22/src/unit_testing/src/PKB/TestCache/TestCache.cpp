//
// Created by Jai Lulla  on 30/3/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

#include "PKB/Exceptions/DataNotFoundInCacheException.cpp"

using namespace std;

TEST_CASE("Test 1: Addition Of Data To Cache") {
    bool anyExceptionThrown = false;

    try {
        ResultTable resultTable = ResultTable(map<string, vector<string>> {});

        PKB pkb = PKB();
        pkb.addToCache("AccessKey_1", &resultTable);
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

    PKB pkb = PKB();
    pkb.addToCache("AccessKey_2", resultTable);
    ResultTable* result = pkb.getResultTableFromCache("AccessKey_2");

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

    PKB pkb = PKB();
    pkb.addToCache("AccessKey_3", resultTableOne);
    pkb.addToCache("AccessKey_4", resultTableTwo);

    ResultTable* resultOne = pkb.getResultTableFromCache("AccessKey_3");
    ResultTable* resultTwo = pkb.getResultTableFromCache("AccessKey_4");

    REQUIRE(((resultOne->equals(*resultTableOne)) && (resultTwo->equals(*resultTableTwo))));
}

TEST_CASE("Test 4: Retrieval Of Data From Cache Which Does Not Exist") {
    bool exceptionThrown = false;

    ResultTable* resultTable = new ResultTable(
            map<string, vector<string>> {
                    make_pair("sample", vector<string> {"sample"})
            });

    PKB pkb = PKB();
    pkb.addToCache("AccessKey_5", resultTable);

    try {
        ResultTable *resultOne = pkb.getResultTableFromCache("InvalidAccessKey");
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

    PKB pkb = PKB();
    pkb.addToCache("AccessKey_6", resultTable);

    unordered_map<string, ResultTable*> db = pkb.getCacheDatabase();
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

    PKB pkb = PKB();
    pkb.addToCache("AccessKey_7", resultTableOne);
    pkb.addToCache("AccessKey_8", resultTableTwo);

    ResultTable* resultOne = pkb.getResultTableFromCache("AccessKey_7");
    ResultTable* resultTwo = pkb.getResultTableFromCache("AccessKey_8");

    bool obtainedCorrectDatabaseBeforeClearing = ((resultOne->equals(*resultTableOne)) && (resultTwo->equals(*resultTableTwo)));

    pkb.clearCache();

    unordered_map<string, ResultTable*> db = pkb.getCacheDatabase();

    REQUIRE(((db.size() == 0) && (obtainedCorrectDatabaseBeforeClearing)));
}
