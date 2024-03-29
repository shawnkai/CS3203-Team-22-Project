//
// Created by Yi Zhang on 12/3/23.
//

#ifndef SPA_CFG_H
#define SPA_CFG_H
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include "queue"
#include <algorithm>
#include "iostream"
#include "vector"
#pragma once

#include "../Parser/TNode.h"

using namespace std;

/**
 * Cfg class stores 5 data structures to comprehensively represents a control flow graph of a single SIMPLE procedure.
 */
class Cfg {
public:
    vector<int> buildCfg(TNode root, int exitParent);
    std::string toString() const;
    std::vector<int> basicBlock;
    std::unordered_map<int, std::vector<int> > blockToStatement;
    std::unordered_map<int, int> statementNumberToBlock;
    std::unordered_map<int, std::vector<int> > blockGraph;
    std::unordered_set<int> blockPointingBackward;


    explicit Cfg(TNode root, vector<int> basicBlock = vector<int>(0), unordered_map<int, vector<int> > blkToStmt = unordered_map<int, vector<int> >(),
                 unordered_map<int, int> stmtNumberToBlk = unordered_map<int, int >(), unordered_map<int, vector<int> > graph = unordered_map<int, vector<int> >(),
                         unordered_set<int> blks = unordered_set<int>())
                 : ast(std::move(root)), basicBlock(std::move(basicBlock)), blockToStatement(std::move(blkToStmt)),
                 statementNumberToBlock(std::move(stmtNumberToBlk)), blockGraph(std::move(graph)),
                 blockPointingBackward(std::move(blks)), currentBlk(1){};
private:
    TNode ast;
    int currentBlk;
    int buildBasicNode(const vector<int>& currentStmts);
    int buildWhileNode(vector<int> currentStmts, TNode statementListToProcess, int pointer);
    vector<int> buildIfNode(vector<int> currentStmts, TNode statementListToProcess, int pointer);
    vector<int> handleLinkingBackBlocks(vector<int> pendingHandling, vector<int> neighbours);
    vector<int> handleTerminalBlocks(const vector<int>& pendingToTerminate);
};

#endif //SPA_CFG_H
