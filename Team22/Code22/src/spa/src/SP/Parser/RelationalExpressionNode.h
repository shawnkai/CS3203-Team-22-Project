
#ifndef SPA_RELATIONALEXPRESSIONNODE_H
#define SPA_RELATIONALEXPRESSIONNODE_H

#include "TreeNode.h"

class RelationalExpressionNode: public TreeNode {
public:
    RelationalExpressionNode() {
        nodeType = TokenType::OPERATOR;
    }
    void accept(DesignExtractor &de) override;
};

#endif //SPA_RELATIONALEXPRESSIONNODE_H
