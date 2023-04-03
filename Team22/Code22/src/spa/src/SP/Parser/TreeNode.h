//
// Created by Yi Zhang on 12/3/23.
//
#ifndef SPA_TREENODE_H
#define SPA_TREENODE_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "../Tokenizer/Token.h"

class TreeNode
{
public:
    TokenType nodeType;
    std::string stringId;
    int stmtNumber;
    std::vector<std::shared_ptr<TreeNode> > children;

    explicit TreeNode(TokenType type = UNKNOWN, const std::string& stringId = "",
                   int stmtNumber = 0,
                   const std::vector<std::shared_ptr<TreeNode>>& children = std::vector<std::shared_ptr<TreeNode>>(0)) :
            nodeType(type), stringId(stringId), stmtNumber(stmtNumber), children(children) {};

    TreeNode(const TreeNode& other) : nodeType(other.nodeType), stringId(other.stringId), stmtNumber(other.stmtNumber){
        for (const auto& child : other.children) {
            children.push_back(std::make_shared<TreeNode>((TreeNode(*child))));
        }
    };

    void accept(class DesignExtractor &de);

};

inline std::string ToString(const TreeNode& t) {
    std::string childrenName;
    for (auto const& child : t.children) {
        childrenName += child->stringId;
    }
    return ToString(t.nodeType) + t.stringId + std::to_string(t.stmtNumber) + " with children: "
           + childrenName;
}

#endif //SPA_TREENODE_H
