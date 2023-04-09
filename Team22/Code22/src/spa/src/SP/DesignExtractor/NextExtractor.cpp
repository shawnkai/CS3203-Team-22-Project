#include <deque>
#include <iostream>
#include <map>
#include <queue>
#include <stdio.h>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

using namespace std;

#include "NextExtractor.h"

void NextExtractor::addWithinBlkNextAbstraction(int blkNo, std::unordered_map<int, vector<int>> blkToStmtMap, PKB pkbinstance) {
    std::string underlineStr = "_";
    if (blkToStmtMap.count(blkNo) > 0) {
        vector<int> stmtInblk = blkToStmtMap.at(blkNo);
        if (stmtInblk.size() > 1) {
            for (int i = 0; i < stmtInblk.size() - 1; i++) {
                int next1 = i + 1;
                pkbinstance.addDesignAbstraction("NEXT", make_tuple(underlineStr, std::to_string(stmtInblk[i]), std::to_string(stmtInblk[next1])));
                cout << std::to_string(stmtInblk[i]) + " next is " + std::to_string(stmtInblk[next1]) << endl;
            }
        } else {
        }
    } else {
    }
};

void NextExtractor::addBtwBlkNextAbstraction(int prevBlk, int nextBlk, std::unordered_map<int, vector<int>> blkToStmtMap, PKB pkbinstance) {
    std::string underlineStr = "_";
    if ((blkToStmtMap.count(prevBlk) > 0) && (blkToStmtMap.count(nextBlk) > 0)) {
        vector<int> stmtInPrevblk = blkToStmtMap.at(prevBlk);
        vector<int> stmtInNextblk = blkToStmtMap.at(nextBlk);
        int lastIdx = stmtInPrevblk.size() - 1;
        pkbinstance.addDesignAbstraction("NEXT", make_tuple(underlineStr, std::to_string(stmtInPrevblk[lastIdx]), std::to_string(stmtInNextblk[0])));
        cout << std::to_string(stmtInPrevblk[lastIdx]) + " next is " + std::to_string(stmtInNextblk[0]) << endl;
    } else {
    }
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
void NextExtractor::extractAbstraction(vector<int> orderedBlks, std::unordered_map<int, vector<int>> blkToStmtMap, std::unordered_map<int, int> stmtToBlkMap, std::unordered_map<int, vector<int>> blkToBlkMap, std::unordered_set<int> setOfWhile, PKB pkbinstance, std::string procedureName) {

    if (orderedBlks.size() == 0) {
        cout << "no blks stored" << endl;
    } else {
        for (int i = 0; i < orderedBlks.size(); i++) {
            int currBlk = orderedBlks[i];
            addWithinBlkNextAbstraction(currBlk, blkToStmtMap, pkbinstance);
            if (blkToBlkMap.count(currBlk) > 0) {
                vector<int> nextBlks = blkToBlkMap.at(currBlk);
                if (nextBlks.size() > 0) {
                    for (int j = 0; j < nextBlks.size(); j++) {
                        addBtwBlkNextAbstraction(currBlk, nextBlks[j], blkToStmtMap, pkbinstance);
                    }
                }
            }
        }
    }
};
        
        /* vector<deque<int>> vector1;
        if (orderedBlks.size() == 1) {
            deque<int> path1;
            path1.push_back(orderedBlks[0]);
            path1.push_back(0);
            vector1.push_back(path1);
            cout << "only 1 block" << endl;
        } else {
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
            cout << "no path" << endl;
        } else if (vector1.size() == 1) {
            deque<int> path2 = vector1[0];
            if (path2.size() == 2) {
                addWithinBlkNextAbstraction(path2[0], blkToStmtMap, pkbinstance);
            } else {
                for (int i = 0; i < path2.size() - 1; i++) {
                    addWithinBlkNextAbstraction(path2[i], blkToStmtMap, pkbinstance);
                }
                for (int i = 0; i < path2.size() - 2; i++) {
                    int next1 = i + 1;
                    addBtwBlkNextAbstraction(path2[i], path2[next1], blkToStmtMap, pkbinstance);
                }
            }
        } else {
            for (int i = 0; i < vector1.size(); i++) {
                deque<int> path2 = vector1[i];
                if (path2.size() == 2) {
                    addWithinBlkNextAbstraction(path2[0], blkToStmtMap, pkbinstance);
                } else {
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
};*/
