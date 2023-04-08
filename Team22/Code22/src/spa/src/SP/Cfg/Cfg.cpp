//
// Created by Yi Zhang on 12/3/23.
//
#include "Cfg.h"
#pragma once
using namespace std;

/**
 * Loops through a statement list node and recursively build the control flow graph for the statement list.
 *
 * @param root TNode containing a statement list
 * @param exitParent Records whether the current statement list is inside a container node
 * @return a vector of int indicating the exiting node(s) from the current basic block
 */
vector<int> Cfg::buildCfg(TNode root, int exitParent) {
    TokenType initial = root.nodeType;
    if (initial != TokenType::PROCEDURE && initial != TokenType::STATEMENT_LIST) {
        cout << "something went wrong" << endl;
    }
    cout << "checking passed, start building cfg" << endl;
    vector<int> currStmts;
    vector<int> thisBlkNeighbour;
    TNode statementListToProcess;
    if (initial == TokenType::PROCEDURE) {
        statementListToProcess = root.children[0];
    }
    else {
        statementListToProcess = root;
    }
    vector<int> pendingLinkingBack;
    for (int i = 0; i < statementListToProcess.children.size(); ++ i) {
        cout << "processing node " + ToString(statementListToProcess.children[i]) << endl;
        if (i < statementListToProcess.children.size() &&
                statementListToProcess.children[i].nodeType != TokenType::WHILE &&
                statementListToProcess.children[i].nodeType != TokenType::IF) {
            currStmts.push_back(statementListToProcess.children[i].stmtNumber);
            continue;
        }
        if (!currStmts.empty()) {
            if (!pendingLinkingBack.empty()) {
                pendingLinkingBack = handleLinkingBackBlocks(pendingLinkingBack, thisBlkNeighbour);
            }
            int exitingBlk = buildBasicNode(currStmts);
            if (i == statementListToProcess.children.size() && exitParent == -1) {
                //link last blk to 0
                vector<int> tempResult;
                tempResult.push_back(exitingBlk);
                vector<int> end = handleTerminalBlocks(tempResult);
                return end;
            }
            pendingLinkingBack.push_back(exitingBlk);
        }
        if (i < statementListToProcess.children.size() &&
        statementListToProcess.children[i].nodeType == TokenType::WHILE) {
            thisBlkNeighbour.clear();
            currStmts.clear();
            if (!pendingLinkingBack.empty()) {
                pendingLinkingBack = handleLinkingBackBlocks(pendingLinkingBack, thisBlkNeighbour);
            }
            int exitingBlk = buildWhileNode(currStmts, statementListToProcess, i);
            if (i == statementListToProcess.children.size() - 1 && exitParent == -1) {
                //link last blk to 0
                vector<int> tempResult;
                tempResult.push_back(exitingBlk);
                vector<int> end = handleTerminalBlocks(tempResult);
                return end;
            }
            pendingLinkingBack.push_back(exitingBlk);
        }
        if (i < statementListToProcess.children.size() &&
        statementListToProcess.children[i].nodeType == TokenType::IF) {
            thisBlkNeighbour.clear();
            currStmts.clear();
            if (!pendingLinkingBack.empty()) {
                pendingLinkingBack = handleLinkingBackBlocks(pendingLinkingBack, thisBlkNeighbour);
            }
            vector<int> exitingBlkVec = buildIfNode(currStmts, statementListToProcess, i);
            if (i == statementListToProcess.children.size() - 1 && root.nodeType == TokenType::PROCEDURE) {
                //link last blk to 0
                vector<int> end = handleTerminalBlocks(exitingBlkVec);
                return end;
            }
            pendingLinkingBack.insert(pendingLinkingBack.end(), exitingBlkVec.begin(), exitingBlkVec.end());
        }
    }
    if (!currStmts.empty()) {
        if (!pendingLinkingBack.empty()) {
            pendingLinkingBack = handleLinkingBackBlocks(pendingLinkingBack, thisBlkNeighbour);
        }
        int exitingBlk = buildBasicNode(currStmts);
        vector<int> result;
        result.push_back(exitingBlk);
        if (root.nodeType == TokenType::PROCEDURE) {
            vector<int> end = handleTerminalBlocks(result);
            return end;
        }
        return result;
    }
    return pendingLinkingBack;
}

/**
 * Link the outermost exiting blocks to basic block 0 to indicate program termination.
 *
 * @param pendingToTerminate
 * @return
 */
vector<int> Cfg::handleTerminalBlocks(const vector<int>& pendingToTerminate) {
    vector<int> end;
    end.push_back(0);
    for(int ending: pendingToTerminate) {
        unordered_map<int, vector<int> >::iterator itr;
        itr = blockGraph.find(ending);
        if (itr == blockGraph.end()) {
            blockGraph.insert(pair<int, vector<int> >(ending, end));
        } else {
            auto existing = itr->second;
            existing.insert(existing.end(), end.begin(), end.end());
            itr->second = existing;
        }
    }
    return end;
}

/**
 * Links exiting blocks from the previous layer to the current basic block being built.
 *
 * @param pendingHandling Exiting blocks from the previous recursive call
 * @param neighbours a vector for temporary storage of neighbours of the exiting blocks
 * @return a cleared vector for the algorithm to continue
 */
vector<int> Cfg::handleLinkingBackBlocks(vector<int> pendingHandling, vector<int> neighbours) {
    for (int entry: pendingHandling) {
        neighbours.push_back(currentBlk);
        unordered_map<int, vector<int> >::iterator itr;
        itr = blockGraph.find(entry);
        if (itr == blockGraph.end()) {
            blockGraph.insert(pair<int, vector<int> >(entry, neighbours));
        } else {
            auto existing = itr->second;
            existing.insert(existing.end(), neighbours.begin(), neighbours.end());
            itr->second = existing;
        }
        neighbours.clear();
    }
    pendingHandling.clear();
    return pendingHandling;
}

/**
 * Build a basic node consisting of only READ/PRINT/CALL statements.
 *
 * @param currentStmts the individual statements inside the basic block
 * @return an int, indicating the exiting block is itself
 */
int Cfg::buildBasicNode(const vector<int>& currentStmts) {
    basicBlock.push_back(currentBlk);
    blockToStatement.insert(pair<int, vector<int> >(currentBlk, currentStmts));
    for (auto stmt : currentStmts) {
        statementNumberToBlock.insert(pair<int, int>(stmt, currentBlk));
    }
    ++ currentBlk;
    return currentBlk - 1;
}

/**
 * Recursively build the while node's basic blocks representation in a CFG.
 *
 * @param currentStmts an empty vector for usage in building the while node
 * @param statementListToProcess the current statement list node under process
 * @param pointer indicates which statement inside the statement list node we are current at
 * @return the basic block number of the condition node of while
 */
int Cfg::buildWhileNode( vector<int> currentStmts, TNode statementListToProcess, int pointer) {
    //build a conditional node's basic block
    currentStmts.push_back((statementListToProcess.children[pointer]).children[0].stmtNumber);
    basicBlock.push_back(currentBlk);
    int exitingNumber = currentBlk;
    blockPointingBackward.insert(exitingNumber);
    blockToStatement.insert(pair<int, vector<int> >(currentBlk, currentStmts));
    for (auto stmt : currentStmts) {
        statementNumberToBlock.insert(pair<int, int>(stmt, currentBlk));
    }
    ++ currentBlk;
    auto subTree = statementListToProcess.children[pointer].children[1];
    vector<int> condNodeNeighbour;
    condNodeNeighbour.push_back(currentBlk);
    //insert the conditional node's info
    blockGraph.insert(pair<int, vector<int> >(exitingNumber, condNodeNeighbour));
    vector<int> exitingBlk = buildCfg(subTree, currentBlk - 1);
    if (exitingBlk.front() == 0) {
        cout << "end node returned to While, something went wrong" << endl;
    }
    // link the exiting node in the stmtList of while back to the conditional node
    unordered_map<int, vector<int> >::iterator itr;
    for (int linkingBack: exitingBlk) {
        itr = blockGraph.find(linkingBack);
        if (itr != blockGraph.end()) {
            auto existing = itr->second;
            existing.push_back(exitingNumber);
            itr->second = existing;
        } else {
            vector<int> condNodeAsANeighbour;
            condNodeAsANeighbour.push_back(exitingNumber);
            blockGraph.insert(pair<int, vector<int> >(linkingBack, condNodeAsANeighbour));
        }
    }
    return exitingNumber;
}

/**
 * Recursively build the IF statement's basic blocks representation in a CFG.
 *
 * @param currentStmts an empty vector for usage in building the if node
 * @param statementListToProcess the current statement list node under process
 * @param pointer indicates which statement inside the statement list node we are current at
 * @return exiting blocks from the if node to be linking to child
 */
vector<int> Cfg::buildIfNode(vector<int> currentStmts, TNode statementListToProcess, int pointer) {
    // process the conditional node of if
    currentStmts.push_back(statementListToProcess.children[pointer].children[0].stmtNumber);
    basicBlock.push_back(currentBlk);
    int cond = currentBlk;
    blockToStatement.insert(pair<int, vector<int> >(currentBlk, currentStmts));
    for (auto stmt : currentStmts) {
        statementNumberToBlock.insert(pair<int, int>(stmt, currentBlk));
    }
    ++ currentBlk;
    auto ifSubTree = statementListToProcess.children[pointer].children[1];
    auto elseSubTree = statementListToProcess.children[pointer].children[2];
    vector<int> condNodeNeighbour;
    condNodeNeighbour.push_back(currentBlk);
    vector<int> ifExitingNumber = buildCfg(ifSubTree, currentBlk - 1);
    if (ifExitingNumber.front() == 0) {
        cout << "end node returned to While, something went wrong" << endl;
    }
    condNodeNeighbour.push_back(currentBlk);
    blockGraph.insert(pair<int, vector<int> >(cond, condNodeNeighbour));
    vector<int> elseExitingNumber = buildCfg(elseSubTree, currentBlk - 1);
    if (elseExitingNumber.front() == 0) {
        cout << "end node returned to While, something went wrong" << endl;
    }
    vector<int> result = ifExitingNumber;
    result.insert(result.end(), elseExitingNumber.begin(), elseExitingNumber.end());
    return result;
}

/**
 * Build a graph representation of the CFG in string for easy visualisation and debugging.
 *
 * @return a string representation of the CFG graph
 */
string Cfg::toString() {
    std::string result;
    result += "BasicBlock List: ";
    for (int basicBlk: basicBlock) {
        result += to_string(basicBlk);
        result += " ";
    }
    result += "\n";
    result += "BlockToStatementMap: ";
    for (auto entry: blockToStatement) {
        int key = entry.first;
        result += to_string(key);
        result += "->";
        string vectorTemp;
        vector<int> value = entry.second;
        for (auto e2: value) {
            vectorTemp += std::to_string(e2);
            vectorTemp += ",";
        }
        result += vectorTemp;
        result += ";";
    }
    result += "\n";
    result += "statementNumberToBlock: ";
    for (auto entry : statementNumberToBlock) {
        int key = entry.first;
        int value = entry.second;
        result += to_string(key);
        result += "->";
        result += to_string(value);
        result += ";";
    }
    result += "\n";
    result += "blockGraph: ";
    for (auto entry: blockGraph) {
        int key = entry.first;
        result += to_string(key);
        result += "->";
        string vectorTemp;
        vector<int> value = entry.second;
        for (auto e2: value) {
            vectorTemp += std::to_string(e2);
            vectorTemp += " ";
        }
        result += vectorTemp;
        result += ";";
    }
    result += "\n";
    result += "BlockPointingBackwards: ";
    for (auto bk: blockPointingBackward) {
        result += to_string(bk);
        result += " ";
    }
    result += "\n";
    return result;
}
