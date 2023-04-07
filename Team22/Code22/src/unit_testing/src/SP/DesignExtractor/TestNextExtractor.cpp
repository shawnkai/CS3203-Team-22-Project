#include "SP/DesignExtractor/NextExtractor.h"
#include "catch.hpp"
using namespace std;
TEST_CASE("Testcase1_ExtractPath_ShouldSuccess") {
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
	NextExtractor nextExtractor;
	vector<deque<int>> results = nextExtractor.findPath(orderedBlks, blkToBlkMap, setOfWhile, 1, 1);
	deque<int> path1;
	path1.push_back(1);
	path1.push_back(2);
	path1.push_back(3);
	path1.push_back(7);
	path1.push_back(0);
	deque<int> path2;
	path2.push_back(1);
	path2.push_back(2);
	path2.push_back(4);
	path2.push_back(5);
	path2.push_back(6);
	path2.push_back(4);
	path2.push_back(7);
	path2.push_back(0);
	deque<int> path3;
	path3.push_back(1);
	path3.push_back(2);
	path3.push_back(4);
	path3.push_back(7);
	path3.push_back(0);
	vector<deque<int>> vector2;
	vector2.push_back(path1);
	vector2.push_back(path2);
	vector2.push_back(path3);
	REQUIRE(results == vector2);
}