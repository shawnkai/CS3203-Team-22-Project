#ifndef SPA_MAINPARSER_H
#define SPA_MAINPARSER_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <sstream>
#include <utility>
#include <unordered_set>
#include "memory"
#include "TreeNode.h"
#include "IfNode.h"
#include "WhileNode.h"
#include "PrintNode.h"
#include "CallNode.h"
#include "AssignNode.h"
#include "ReadNode.h"
#include "ConditionalExpressionNode.h"
#include "ExpressionNode.h"
#include "RelationalExpressionNode.h"
#include "RelationalFactorNode.h"
#include "FactorNode.h"
#include "TermNode.h"
#include "ProcedureNode.h"
#include "ProgramNode.h"
#include "VarNode.h"
#include "ConstantNode.h"

class MainParser {
public:
    MainParser(const std::vector<Token>& tokenList, std::shared_ptr<int> pos) : tokenList(tokenList), pos(std::move(pos)) {}

    virtual TreeNode parse() {
        std::cout << "Main Parser's parse should never be called" << std::endl;
        throw std::runtime_error("Should not call MainParser's parse");
    }

protected:
    const std::vector<Token>& tokenList;
    std::shared_ptr<int> pos;
};

#endif //SPA_MAINPARSER_H
