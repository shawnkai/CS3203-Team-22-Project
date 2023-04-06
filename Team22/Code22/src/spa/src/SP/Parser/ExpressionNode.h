
#ifndef SPA_EXPRESSIONNODE_H
#define SPA_EXPRESSIONNODE_H

#include "TreeNode.h"

class ExpressionNode: public TreeNode {
public:
    void accept(DesignExtractor &de) override;
};

#endif //SPA_EXPRESSIONNODE_H
