//
// Created by Yi Zhang on 3/4/23.
//

#ifndef SPA_STATEMENTLISTNODE_H
#define SPA_STATEMENTLISTNODE_H
#include "TreeNode.h"

class StatementListNode : public TreeNode {
public:
    StatementListNode() {
        nodeType = TokenType::STATEMENT_LIST;
    }
    void accept(DesignExtractor& de);
};


#endif //SPA_STATEMENTLISTNODE_H
