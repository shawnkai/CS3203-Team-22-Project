#include "SP/DesignExtractor/NextExtractor.h"
#include "catch.hpp"
using namespace std;
TEST_CASE("Testcase1_ExtractNext_ShouldSuccess") {
    vector<int> orderedBlks;
    orderedBlks.push_back(1);
    orderedBlks.push_back(2);
    orderedBlks.push_back(3);
    orderedBlks.push_back(4);
    orderedBlks.push_back(5);
    orderedBlks.push_back(6);
    orderedBlks.push_back(7);
    std::unordered_map<int, vector<int>> blkToBlkMap;
    vector<int> v1;
    v1.push_back(2);
    blkToBlkMap[1] = v1;

    vector<int> v2;
    v2.push_back(3);
    v2.push_back(4);
    blkToBlkMap[2] = v2;

    vector<int> v3;
    v3.push_back(7);
    blkToBlkMap[3] = v3;

    vector<int> v4;
    v4.push_back(5);
    v4.push_back(7);
    blkToBlkMap[4] = v4;

    vector<int> v5;
    v5.push_back(6);
    blkToBlkMap[5] = v5;

    vector<int> v6;
    v6.push_back(4);
    blkToBlkMap[6] = v6;

    vector<int> v7;
    v7.push_back(0);
    blkToBlkMap[7] = v7;

    std::unordered_set<int> setOfWhile;
    setOfWhile.insert(4);

    std::unordered_map<int, vector<int>> blkToStmtMap;
    for (int i = 1; i < 8; i++) {
        vector<int> v1;
        v1.push_back(i);
        blkToStmtMap[i] = v1;
    }

    std::unordered_map<int, int> stmtToBlkMap;
    for (int i = 1; i < 8; i++) {
        stmtToBlkMap[i] = i;
    }

    PKB pkbinstance = PKB();
    pkbinstance.clearAllDatabases("CalledForTestingPurposes");
    
    NextExtractor nextExtractor;
    nextExtractor.extractAbstraction(orderedBlks, blkToStmtMap, stmtToBlkMap, blkToBlkMap, setOfWhile, pkbinstance, "procedure1");

    std::string result1 = pkbinstance.getDesignAbstraction("NEXT", make_tuple("_", std::to_string(2))).toString();

    REQUIRE(result1 == "NEXT: 2: 3, 4, ");



}