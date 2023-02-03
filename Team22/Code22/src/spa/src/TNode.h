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
std::vector<std::unique_ptr<TNode>> children;

explicit TNode(TokenType type = UNKNOWN, std::string stringId = "",
               int stmtNumber = 0,
               std::vector<std::unique_ptr<TNode>> children = {}) :
               nodeType(type), stringId(std::move(stringId)), stmtNumber(stmtNumber), children(std::move(children)) {};
};