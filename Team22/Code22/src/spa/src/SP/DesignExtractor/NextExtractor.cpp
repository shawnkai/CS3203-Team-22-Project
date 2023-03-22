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

#include "NextExtractor.h"

void NextExtractor::addWithinBlkNextAbstraction(int blkNo, std::map<int, vector<int>> blkToStmtMap, PKB pkbinstance) {
	if (blkToStmtMap.count(blkNo) > 0) {
		vector<int> stmtInblk = blkToStmtMap.at(blkNo);
		if (stmtInblk.size() > 1) {
			for (int i = 0; i < stmtInblk.size() - 1; i++) {
				int next1 = i + 1;
				pkbinstance.addDesignAbstraction("NEXT", make_tuple("_", std::to_string(stmtInblk[0]), std::to_string(stmtInblk[next1])));
				cout << std::to_string(stmtInblk[0]) + " next is " + std::to_string(stmtInblk[next1]) << endl;
			}
		}
		else {
		}
	}
	else {
	}

};

void NextExtractor::addBtwBlkNextAbstraction(int prevBlk, int nextBlk, std::map<int, vector<int>> blkToStmtMap, PKB pkbinstance) {
	if ((blkToStmtMap.count(prevBlk) > 0) && (blkToStmtMap.count(nextBlk) > 0)) {
		vector<int> stmtInPrevblk = blkToStmtMap.at(prevBlk);
		vector<int> stmtInNextblk = blkToStmtMap.at(nextBlk);
		int lastIdx = stmtInPrevblk.size() - 1;
		pkbinstance.addDesignAbstraction("NEXT", make_tuple("_", std::to_string(stmtInPrevblk[lastIdx]), std::to_string(stmtInNextblk[0])));
		cout << std::to_string(stmtInPrevblk[lastIdx]) + " next is " + std::to_string(stmtInNextblk[0]) << endl;
	}
	else {
	}

};

vector<deque<int>> NextExtractor::findPath(vector<int> orderedBlks, std::map<int, vector<int>> blkToBlkMap, std::unordered_set<int> setOfWhile, int nextBlk, int currBlk) {
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
				for (int i = 0; i < pathOfElse.size(); i++) {
					deque<int> pathOfElse1 = pathOfElse[i];
					pathOfElse1.push_front(currBlk);
					allPaths.push_back(pathOfElse1);
				}

			}
			else if (setOfWhile.count(currBlk) > 0) {
				vector<deque<int>> returned = findWhilePath(orderedBlks, blkToBlkMap, setOfWhile, nextBlks[0], currBlk);
				vector<deque<int>> path2 = findPath(orderedBlks, blkToBlkMap, setOfWhile, nextBlk, nextBlks[1]);
				for (int j = 0; j < path2.size(); j++) {
					for (int q = 0; q < returned.size(); q++) {
						deque<int> returned1 = returned[q];
						deque<int> path22 = path2[j];
						for (int i = returned1.size() - 1; i >= 0; i--) {
							path22.push_front(returned1[i]);
						}
						path22.push_front(currBlk);
						allPaths.push_back(path22);
					}
						
				}
				for (int j = 0; j < path2.size(); j++) {
					deque<int> path23 = path2[j];
					path23.push_front(currBlk);
					allPaths.push_back(path23);
						
				}
				for (int i = 0; i < allPaths.size(); i++) {
					deque<int> result1 = allPaths[i];

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
	}
	else {
		if (blkToBlkMap.count(currBlk) > 0) {
			vector<int> nextBlks = blkToBlkMap.at(currBlk);
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
				vector<deque<int>> returned = findWhileStmtlstPath(orderedBlks, blkToBlkMap, setOfWhile, nextBlk, nextBlks[0], currBlk);
				vector<deque<int>> path2 = findWhileStmtlstPath(orderedBlks, blkToBlkMap, setOfWhile, nextBlk, nextBlks[1], exitWhile);
				for (int j = 0; j < path2.size(); j++) {
					for (int q = 0; q < returned.size(); q++) {
						deque<int> returned1 = returned[q];
						deque<int> path22 = path2[j];
						for (int i = returned1.size() - 1; i >= 0; i--) {
							path22.push_front(returned1[i]);
						}
						path22.push_front(currBlk);
						allPaths.push_back(path22);
					}
				}
				for (int j = 0; j < path2.size(); j++) {
					deque<int> path23 = path2[j];
					path23.push_front(currBlk);
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
	return findWhileStmtlstPath(orderedBlks, blkToBlkMap, setOfWhile, whileBlk, currBlk, whileBlk);
			
		
};

/**
 * Extracts the next relationships from the CFG and adds the abstractions to the Program 
 * Knowledge Base.
 *
 * @param orderedBlks The blocks of CFG.
 * @param blkToStmtMap The map from block number to its corresponding statement numbers.
 * @param stmtToBlkMap The map from statement number to its corresponding block number.
 * @param blkToBlkMap The map from block number to the blocks it is connected to.
 * @param setOfWhile The set of while blocks.
 * @param pkbinstance The instance of Program Knowledge Base.
 * @param procedureName The name of the procedure.
 */
void NextExtractor::extractAbstraction(vector<int> orderedBlks, std::map<int, vector<int>> blkToStmtMap, std::map<int, int> stmtToBlkMap, std::map<int, vector<int>> blkToBlkMap, std::unordered_set<int> setOfWhile, PKB pkbinstance, std::string procedureName) {

	if (orderedBlks.size() == 0) {
		cout << "no blks stored" << endl;
	}
	else {
		vector<deque<int>> vector1;
		if (orderedBlks.size() == 1) {
			deque<int> path1;
			path1.push_back(orderedBlks[0]);
			vector1.push_back(path1);
			cout << "only 1 block" << endl;
		}
		else {
			cout << "enter the find path" << endl;
			cout << std::to_string(orderedBlks[0]) << endl;
			vector1 = findPath(orderedBlks, blkToBlkMap, setOfWhile, orderedBlks[0], orderedBlks[0]);
			for (int i = 0; i < vector1.size(); i++) {
				deque<int> result1 = vector1[i];
				cout << "start" << endl;
				for (int i = 0; i < result1.size(); i++) {
					cout << std::to_string(result1[i]) << endl;
				}
			}
		}
		if (vector1.size() == 0) {
			cout << "no blks stored" << endl;
		}
		else if (vector1.size() == 1) {
			deque<int> path2 = vector1[0];
			if (path2.size() == 2) {
				addWithinBlkNextAbstraction(path2[0], blkToStmtMap, pkbinstance);
			}
			else {
				for (int i = 0; i < path2.size() - 1; i++) {
					addWithinBlkNextAbstraction(path2[i], blkToStmtMap, pkbinstance);

				}
				for (int i = 0; i < path2.size() - 2; i++) {
					int next1 = i + 1;
					addBtwBlkNextAbstraction(path2[i], path2[next1], blkToStmtMap, pkbinstance);

				}
			}
		}
		else {
			for (int i = 0; i < vector1.size(); i++) {
				deque<int> path2 = vector1[0];
				if (path2.size() == 2) {
					addWithinBlkNextAbstraction(path2[0], blkToStmtMap, pkbinstance);
				}
				else {
					for (int i = 0; i < path2.size() - 1; i++) {
						addWithinBlkNextAbstraction(path2[i], blkToStmtMap, pkbinstance);

					}
					for (int i = 0; i < path2.size() - 2; i++) {
						int next1 = i + 1;
						addBtwBlkNextAbstraction(path2[i], path2[next1], blkToStmtMap, pkbinstance);

					}
				}

			}
		}
	}
};
		