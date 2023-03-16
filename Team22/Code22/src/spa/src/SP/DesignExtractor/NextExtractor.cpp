#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <map>
#include <unordered_set>
#include <deque>

using namespace std;

//#include "NextExtractor.h"

class NextExtractor {
public:
	NextExtractor() {

	};

	void NextExtractor::extractAbstraction(vector<int> orderedBlks, std::map<int, vector<int>> blkToStmtMap, std::map<int, int> stmtToBlkMap, std::map<int, vector<int>> blkToBlkMap, std::unordered_set<int> setOfWhile) {
		if (orderedBlks.size() == 0) {
			cout << "no blks stored" << endl;
		}
		else {
			if (orderedBlks.size() == 1) {
				
			}
			else {
				
			}
		}
	};

	vector<deque<int>> NextExtractor::findPath(vector<int> orderedBlks, std::map<int, vector<int>> blkToBlkMap, std::unordered_set<int> setOfWhile, int nextBlk, int currBlk) {
		/*int noOfBlks = currentPath.size();
		int endIdx = noOfBlks - 1;
		int currentBlkNo = currentPath[endIdx];*/
		vector<deque<int>> allPaths;
	
		if (currBlk == 0) {
			deque<int> finalPath;
			finalPath.push_back(0);
			allPaths.push_back(finalPath);
		}
		else {
			if (blkToBlkMap.count(currBlk) > 0) {
				vector<int> nextBlks = blkToBlkMap.at(currBlk);
				int size2 = nextBlks.size();
				if ((size2 > 1)&&(setOfWhile.count(currBlk)==0)) {
					vector<deque<int>> pathOfIf = findPath(orderedBlks, blkToBlkMap, setOfWhile, nextBlk, nextBlks[0]);
					vector<deque<int>> pathOfElse = findPath(orderedBlks, blkToBlkMap, setOfWhile, nextBlk, nextBlks[1]);
					for (int i = 0; i < pathOfIf.size(); i++) {
						deque<int> pathOfIf1 = pathOfIf[i];
						pathOfIf1.push_front(currBlk);
						allPaths.push_back(pathOfIf1);
					}
					for (int i = 0; i < pathOfIf.size(); i++) {
						deque<int> pathOfElse1 = pathOfElse[i];
						pathOfElse1.push_front(currBlk);
						allPaths.push_back(pathOfElse1);
					}

				}
				else if (setOfWhile.count(currBlk) > 0) {
					//go through while stmtlst
					vector<deque<int>> returned = findWhilePath(orderedBlks, blkToBlkMap, setOfWhile, nextBlks[0], currBlk);
					//returned.push_back(currBlk);
					//returned.push_front(nextBlks[1]);
					vector<deque<int>> path2 = findPath(orderedBlks, blkToBlkMap, setOfWhile, nextBlk, nextBlks[1]);//shld also handle when this is empty
					//vector<deque<int>> path3 = path2;
					for (int j = 0; j < path2.size(); j++) {
						for (int q = 0; q < returned.size(); q++) {
							deque<int> returned1 = returned[q];
							deque<int> path22 = path2[j];
							for (int i = returned1.size() - 1; i >= 0; i--) {
								path22.push_front(returned1[i]);
								/*cout << "note" << endl;
								cout << std::to_string(returned1[i]) << endl;
								cout << "note" << endl;*/
							}
							path22.push_front(currBlk);
							allPaths.push_back(path22);
							
						}
						
					}
					for (int j = 0; j < path2.size(); j++) {
						deque<int> path23 = path2[j];
						path23.push_front(currBlk);//don't go thru while stmtlist
						allPaths.push_back(path23);
					}

					
				}
				else {
					vector<deque<int>> nextPath = findPath(orderedBlks, blkToBlkMap, setOfWhile, nextBlk, nextBlks[0]);
					for (int j = 0; j < nextPath.size(); j++) {
						deque<int> nextPath1 = nextPath[j];
						nextPath1.push_front(currBlk);
						allPaths.push_back(nextPath1);
					}
					
					
				}
			}
			else {
				cout << "something is wrong" << endl;
			}
			
		}

		return allPaths;
	};

	vector<deque<int>> NextExtractor::findWhileStmtlstPath(vector<int> orderedBlks, std::map<int, vector<int>> blkToBlkMap, std::unordered_set<int> setOfWhile, int nextBlk, int currBlk, int exitWhile) {
		vector<deque<int>> allPaths;
		if (currBlk == 0) {
			cout << "return 0 in while stmtlist" << endl;
		}
		else if (currBlk == exitWhile) {
			deque<int> result;
			result.push_back(exitWhile);
			allPaths.push_back(result);
			
			//return result;
		}
		else {
			if (blkToBlkMap.count(currBlk) > 0) {
				vector<int> nextBlks = blkToBlkMap.at(currBlk);//any branch is definitely if or while
				int size2 = nextBlks.size();
				if ((size2 > 1) && (setOfWhile.count(currBlk) == 0)) {
					vector<deque<int>> pathOfIf = findWhileStmtlstPath(orderedBlks, blkToBlkMap, setOfWhile, nextBlk, nextBlks[0], exitWhile);
					vector<deque<int>> pathOfElse = findWhileStmtlstPath(orderedBlks, blkToBlkMap, setOfWhile, nextBlk, nextBlks[1], exitWhile);
					for (int i = 0; i < pathOfIf.size(); i++) {
						deque<int> pathOfIf1 = pathOfIf[i];
						pathOfIf1.push_front(currBlk);
						allPaths.push_back(pathOfIf1);
					}
					for (int i = 0; i < pathOfIf.size(); i++) {
						deque<int> pathOfElse1 = pathOfElse[i];
						pathOfElse1.push_front(currBlk);
						allPaths.push_back(pathOfElse1);
					}

				}
				else if (setOfWhile.count(currBlk) > 0) {
					//go through while stmtlst
					vector<deque<int>> returned = findWhilePath(orderedBlks, blkToBlkMap, setOfWhile, nextBlks[0], currBlk);
					//returned.push_back(currBlk);
					//returned.push_front(nextBlks[1]);
					vector<deque<int>> path2 = findWhileStmtlstPath(orderedBlks, blkToBlkMap, setOfWhile, nextBlk, nextBlks[1], exitWhile);
					//vector<deque<int>> path3 = path2;
					for (int j = 0; j < path2.size(); j++) {
						for (int q = 0; q < returned.size(); q++) {
							deque<int> returned1 = returned[q];
							deque<int> path22 = path2[j];
							for (int i = returned.size() - 1; i >= 0; i--) {
								path22.push_front(returned1[i]);
							}
							path22.push_front(currBlk);
							allPaths.push_back(path22);
						}

					}
					for (int j = 0; j < path2.size(); j++) {
						deque<int> path23 = path2[j];
						path23.push_front(currBlk);//don't go thru while stmtlist
						allPaths.push_back(path23);
					}

					
				}
				else {
					vector<deque<int>> nextPath = findWhileStmtlstPath(orderedBlks, blkToBlkMap, setOfWhile, nextBlk, nextBlks[0], exitWhile);
					
					for (int j = 0; j < nextPath.size(); j++) {
						deque<int> nextPath1 = nextPath[j];
						nextPath1.push_front(currBlk);
						allPaths.push_back(nextPath1);
					}


				}
				
			}
			else {
				cout << "something is wrong" << endl;
			}
			
		}
		return allPaths;
	};

	vector<deque<int>> NextExtractor::findWhilePath(vector<int> orderedBlks, std::map<int, vector<int>> blkToBlkMap, std::unordered_set<int> setOfWhile, int currBlk, int whileBlk) {
		/*int noOfBlks = currentPath.size();
		int endIdx = noOfBlks - 1;
		int currentBlkNo = currentPath[endIdx];*/
		
		
		//vector<int> nextBlks = blkToBlkMap.at(currBlk);
		return findWhileStmtlstPath(orderedBlks, blkToBlkMap, setOfWhile, whileBlk, currBlk, whileBlk);
			
		
	};
};

/*int main() {
	vector<int> orderedBlks;
	orderedBlks.push_back(1);
	orderedBlks.push_back(2);
	orderedBlks.push_back(3);
	orderedBlks.push_back(4);
	orderedBlks.push_back(5);
	orderedBlks.push_back(6);
	orderedBlks.push_back(7);
	std::map<int, vector<int>> blkToBlkMap;
	vector<int> v1;
	v1.push_back(2);
	blkToBlkMap[1] = v1;

	vector<int> v2;
	v2.push_back(3);
	v2.push_back(4);
	blkToBlkMap[2] = v2;

	vector<int> v3;
	v3.push_back(2);
	blkToBlkMap[3] = v3;

	vector<int> v4;
	v4.push_back(5);
	v4.push_back(6);
	blkToBlkMap[4] = v4;

	vector<int> v5;
	v5.push_back(7);
	blkToBlkMap[5] = v5;

	vector<int> v6;
	v6.push_back(7);
	blkToBlkMap[6] = v6;

	vector<int> v7;
	v7.push_back(0);
	blkToBlkMap[7] = v7;

	cout << "a" << endl;
	std::unordered_set<int> setOfWhile;
	setOfWhile.insert(2);
	NextExtractor nextExtractor;
	vector<deque<int>> results = nextExtractor.findPath(orderedBlks, blkToBlkMap, setOfWhile, 1, 1);
	for (int i = 0; i < results.size(); i++) {
		deque<int> result1 = results[i];
		cout << "start" << endl;
		for (int i = 0; i < result1.size(); i++) {
			cout << std::to_string(result1[i]) << endl;
		}

	}
	//findPath(orderedBlks, blkToBlkMap, setOfWhile, nextBlk, nextBlks[0]);
}*/
		