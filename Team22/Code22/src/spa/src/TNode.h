#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "Token.h"

/* Copied from discussion:
 * struct TNode {
 *     Token operator; --> stmtType: read
 *     int lineNumber;
 *     NameSpace identifier;
 *     std::vector<TNode> children;
 * }
 */

class TNode
{
public:
TokenType nodeType;
std::string stringId;
int stmtNumber;
std::vector<TNode> children;

explicit TNode(TokenType type = UNKNOWN, const std::string& stringId = "",
               int stmtNumber = 0,
               const std::vector<TNode>& children = std::vector<TNode>(0)) :
               nodeType(type), stringId(stringId), stmtNumber(stmtNumber), children(children) {};

};

inline std::string ToString(const TNode& t) {
    std::string childrenName;
    for (auto const& child : t.children) {
        childrenName += child.stringId;
    }
    return ToString(t.nodeType) + t.stringId + std::to_string(t.stmtNumber) + " with children: "
    + childrenName;
}
