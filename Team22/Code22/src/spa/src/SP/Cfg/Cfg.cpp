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
                for (int entry: pendingLinkingBack) {
                    thisBlkNeighbour.push_back(currentBlk);
                    map<int, vector<int> >::iterator itr;
                    itr = blockGraph.find(entry);
                    if (itr == blockGraph.end()) {
                        blockGraph.insert(pair<int, vector<int> >(entry, thisBlkNeighbour));
                    }else{
                        auto existing = itr->second;
                        existing.insert(existing.end(), thisBlkNeighbour.begin(), thisBlkNeighbour.end());
                        itr->second = existing;
                    }
                    thisBlkNeighbour.clear();
                }
                pendingLinkingBack.clear();
            }
            int exitingBlk = buildBasicNode(currStmts);
            if (i == statementListToProcess.children.size() && exitParent == -1) {
                //link last blk to 0
                vector<int> end;
                end.push_back(0);
                blockGraph.insert(pair<int, vector<int> >(exitingBlk, end));
                return end;
            }
            pendingLinkingBack.push_back(exitingBlk);
        }
        if (i < statementListToProcess.children.size() &&
        statementListToProcess.children[i].nodeType == TokenType::WHILE) {
            thisBlkNeighbour.clear();
            currStmts.clear();
            if (!pendingLinkingBack.empty()) {
                for (int entry: pendingLinkingBack) {
                    thisBlkNeighbour.push_back(currentBlk);
                    map<int, vector<int> >::iterator itr;
                    itr = blockGraph.find(entry);
                    if (itr == blockGraph.end()) {
                        blockGraph.insert(pair<int, vector<int> >(entry, thisBlkNeighbour));
                    }else{
                        auto existing = itr->second;
                        existing.insert(existing.end(), thisBlkNeighbour.begin(), thisBlkNeighbour.end());
                        itr->second = existing;
                    }
                    thisBlkNeighbour.clear();
                }
                pendingLinkingBack.clear();
            }
            int exitingBlk = buildWhileNode(currStmts, statementListToProcess, i);
            if (i == statementListToProcess.children.size() - 1 && exitParent == -1) {
                //link last blk to 0
                vector<int> end;
                end.push_back(0);
                map<int, vector<int> >::iterator itr;
                itr = blockGraph.find(exitingBlk);
                if (itr == blockGraph.end()) {
                    blockGraph.insert(pair<int, vector<int> >(exitingBlk, end));
                }else{
                    auto existing = itr->second;
                    existing.insert(existing.end(), end.begin(), end.end());
                    itr->second = existing;
                }
                return end;
            }

            pendingLinkingBack.push_back(exitingBlk);
        }
        if (i < statementListToProcess.children.size() &&
        statementListToProcess.children[i].nodeType == TokenType::IF) {
            thisBlkNeighbour.clear();
            currStmts.clear();
            if (!pendingLinkingBack.empty()) {
                for (int entry: pendingLinkingBack) {
                    thisBlkNeighbour.push_back(currentBlk);
                    map<int, vector<int> >::iterator itr;
                    itr = blockGraph.find(entry);
                    if (itr == blockGraph.end()) {
                        blockGraph.insert(pair<int, vector<int> >(entry, thisBlkNeighbour));
                    }else{
                        auto existing = itr->second;
                        existing.insert(existing.end(), thisBlkNeighbour.begin(), thisBlkNeighbour.end());
                        itr->second = existing;
                    }
                    thisBlkNeighbour.clear();
                }
                pendingLinkingBack.clear();
            }
            vector<int> exitingBlkVec = buildIfNode(currStmts, statementListToProcess, i);
            if (i == statementListToProcess.children.size() - 1 && root.nodeType == TokenType::PROCEDURE) {
                //link last blk to 0
                vector<int> end;
                end.push_back(0);
                for (int pendingToEnd: exitingBlkVec) {
                    map<int, vector<int> >::iterator itr;
                    itr = blockGraph.find(pendingToEnd);
                    if (itr == blockGraph.end()) {
                        blockGraph.insert(pair<int, vector<int> >(pendingToEnd, end));
                    }else{
                        auto existing = itr->second;
                        existing.insert(existing.end(), end.begin(), end.end());
                        itr->second = existing;
                    }
                }
                return end;
            }
            pendingLinkingBack.insert(pendingLinkingBack.end(), exitingBlkVec.begin(), exitingBlkVec.end());
        }
    }
    if (!currStmts.empty()) {
        if (!pendingLinkingBack.empty()) {
            for (int entry: pendingLinkingBack) {
                thisBlkNeighbour.push_back(currentBlk);
                map<int, vector<int> >::iterator itr;
                itr = blockGraph.find(entry);
                if (itr == blockGraph.end()) {
                    blockGraph.insert(pair<int, vector<int> >(entry, thisBlkNeighbour));
                }else{
                    auto existing = itr->second;
                    existing.insert(existing.end(), thisBlkNeighbour.begin(), thisBlkNeighbour.end());
                    itr->second = existing;
                }
                thisBlkNeighbour.clear();
            }
            pendingLinkingBack.clear();
        }
        int exitingBlk = buildBasicNode(currStmts);
        vector<int> result;
        result.push_back(exitingBlk);
        if (root.nodeType == TokenType::PROCEDURE) {
            vector<int> end;
            end.push_back(0);
            blockGraph.insert(pair<int, vector<int> >(exitingBlk, end));
            return end;
        }
        return result;
    }
    return pendingLinkingBack;
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
    currentStmts.push_back(statementListToProcess.children[pointer].children[0].stmtNumber);
    basicBlock.push_back(currentBlk);
    int exitingNumber = currentBlk;
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
    map<int, vector<int> >::iterator itr;
    for (int linkingBack: exitingBlk) {
        blockPointingBackward.insert(linkingBack);
        itr = blockGraph.find(linkingBack);
        if (itr != blockGraph.end()) {
            auto existing = itr->second;
            existing.push_back(linkingBack);
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

int main() {
    TNode root;
    root.nodeType = TokenType::PROCEDURE;
    root.stringId = "example";
    TNode statementListNode;
    statementListNode.nodeType = TokenType::STATEMENT_LIST;
    statementListNode.stringId = "stmtList";
    TNode readNode;
    readNode.nodeType = TokenType::READ;
    readNode.stringId = "read";
    readNode.stmtNumber = 1;
    TNode varNode;
    varNode.nodeType = TokenType::NAME_IDENTIFIER;
    varNode.stringId = "x";
    varNode.stmtNumber = 1;
    TNode readNode2;
    readNode2.nodeType = TokenType::READ;
    readNode2.stringId = "read";
    readNode2.stmtNumber = 7;
    TNode varNode2;
    varNode2.nodeType = TokenType::NAME_IDENTIFIER;
    varNode2.stringId = "y";
    varNode2.stmtNumber = 4;
    readNode.children.push_back(varNode);
    readNode2.children.push_back(varNode2);
    TNode whileNode;
    whileNode.nodeType = TokenType::WHILE;
    whileNode.stringId = "while";
    whileNode.stmtNumber = 2;
    TNode condition;
    condition.nodeType = TokenType::OPERATOR;
    condition.stringId = "<";
    condition.stmtNumber = 2;
    TNode condition2;
    condition2.nodeType = TokenType::OPERATOR;
    condition2.stringId = "==";
    condition2.stmtNumber = 4;
    TNode varNode3;
    varNode3.nodeType = TokenType::NAME_IDENTIFIER;
    varNode3.stringId = "i";
    varNode3.stmtNumber = 2;
    TNode intNode;
    intNode.nodeType = TokenType::INTEGER;
    intNode.stringId = "1";
    intNode.stmtNumber = 2;
    TNode readNode3;
    readNode3.nodeType = TokenType::READ;
    readNode3.stringId = "";
    readNode3.stmtNumber = 5;
    TNode varNode4;
    varNode4.nodeType = TokenType::NAME_IDENTIFIER;
    varNode4.stringId = "i";
    varNode4.stmtNumber = 3;
    TNode statementListNode2;
    statementListNode2.nodeType = TokenType::STATEMENT_LIST;
    statementListNode2.stringId = "stmtList";
    statementListNode2.stmtNumber = 5;
    readNode3.children.push_back(varNode4);
    condition.children.push_back(varNode3);
    condition.children.push_back(intNode);
    whileNode.children.push_back(condition2);
    statementListNode2.children.push_back(readNode3);
    //whileNode.children.push_back(statementListNode2);
    TNode ifNode;
    ifNode.nodeType = TokenType::IF;
    ifNode.stringId = "if";
    ifNode.stmtNumber = 2;
    TNode statementListNode3;
    statementListNode3.nodeType = TokenType::STATEMENT_LIST;
    statementListNode3.stringId = "if";
    statementListNode3.stmtNumber = 3;
    TNode statementListNode4;
    statementListNode4.nodeType = TokenType::STATEMENT_LIST;
    statementListNode4.stringId = "else";
    statementListNode4.stmtNumber = 3;
    TNode printNode1;
    printNode1.nodeType = TokenType::PRINT;
    printNode1.stringId = "print";
    printNode1.stmtNumber = 3;
    TNode printNode2;
    printNode2.nodeType = TokenType::PRINT;
    printNode2.stringId = "print";
    printNode2.stmtNumber = 6;
    TNode varNode5;
    varNode5.nodeType = TokenType::NAME_IDENTIFIER;
    varNode5.stringId = "i";
    varNode5.stmtNumber = 3;
    TNode varNode6;
    varNode6.nodeType = TokenType::NAME_IDENTIFIER;
    varNode6.stringId = "i";
    varNode6.stmtNumber = 6;
    printNode1.children.push_back(varNode5);
    printNode2.children.push_back(varNode6);

    statementListNode3.children.push_back(printNode1);
    //statementListNode3.children.push_back(whileNode);
    statementListNode4.children.push_back(printNode2);
    ifNode.children.push_back(condition);
    ifNode.children.push_back(statementListNode3);
    ifNode.children.push_back(statementListNode4);
    statementListNode2.children.push_back(ifNode);
    whileNode.children.push_back(statementListNode2);
    statementListNode.children.push_back(readNode);
    //statementListNode.children.push_back(whileNode);
    //statementListNode.children.push_back(ifNode);
    statementListNode.children.push_back(whileNode);
    //statementListNode.children.push_back(printNode1);
    statementListNode.children.push_back(readNode2);
    root.children.push_back(statementListNode);
    cout << ToString(root) << endl;
    cout << ToString(statementListNode) << endl;
    cout << to_string(statementListNode.children.size()) << endl;
    cout << ToString(statementListNode3) << endl;
    Cfg cfgTest = Cfg(root);
    cfgTest.buildCfg(root, -1);
    cout << cfgTest.toString() << endl;
    return 0;
}