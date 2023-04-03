
#ifndef SPA_CONDITIONALEXPRESSIONNODE_H
#define SPA_CONDITIONALEXPRESSIONNODE_H

#include "TreeNode.h"

class ConditionalExpressionNode: public TreeNode {
public:
    ConditionalExpressionNode() {
        nodeType = TokenType::OPERATOR;
    }

    void accept(DesignExtractor &de);
};

#endif //SPA_CONDITIONALEXPRESSIONNODE_H
