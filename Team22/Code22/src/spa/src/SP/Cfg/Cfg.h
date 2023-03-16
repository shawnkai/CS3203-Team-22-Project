//
// Created by Yi Zhang on 12/3/23.
//

#ifndef SPA_CFG_H
#define SPA_CFG_H
#include <utility>
#include <map>
#include <unordered_set>
#include "queue"
#include <algorithm>
#include "iostream"
#include "vector"
#pragma once

#include "../Parser/TNode.h"
#include "../Parser/Parser.h"
#include "../Tokenizer/Tokenizer.h"
using namespace std;

class Cfg {
public:
    vector<int> buildCfg(TNode root, int exitParent);
    std::string toString();
    std::vector<int> basicBlock;
    std::map<int, std::vector<int> > blockToStatement;
    std::map<int, int> statementNumberToBlock;
    std::map<int, std::vector<int> > blockGraph;
    std::unordered_set<int> blockPointingBackward;

    explicit Cfg(TNode root, vector<int> basicBlock = vector<int>(0), map<int, vector<int> > blkToStmt = map<int, vector<int> >(),
                 map<int, int> stmtNumberToBlk = map<int, int >(), map<int, vector<int> > graph = map<int, vector<int> >(),
                         unordered_set<int> blks = unordered_set<int>())
                 : ast(std::move(root)), basicBlock(basicBlock), blockToStatement(std::move(blkToStmt)),
                 statementNumberToBlock(std::move(stmtNumberToBlk)), blockGraph(std::move(graph)),
                 blockPointingBackward(std::move(blks)), currentBlk(1){};
private:
    TNode ast;
    int currentBlk;
    int buildBasicNode(const vector<int>& currentStmts);
    int buildWhileNode(vector<int> currentStmts, TNode statementListToProcess, int pointer);
    vector<int> buildIfNode(vector<int> currentStmts, TNode statementListToProcess, int pointer);
    //vector<int> pendingLinkingBack;
};

#endif //SPA_CFG_H
