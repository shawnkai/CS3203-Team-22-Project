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
