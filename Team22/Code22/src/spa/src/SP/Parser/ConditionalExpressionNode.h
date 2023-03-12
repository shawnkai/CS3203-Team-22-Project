
#ifndef SPA_CONDITIONALEXPRESSIONNODE_H
#define SPA_CONDITIONALEXPRESSIONNODE_H

#include "TreeNode.h"

class ConditionalExpressionNode: public TreeNode {
public:
    void accept(DesignExtractor &de);
};

#endif //SPA_CONDITIONALEXPRESSIONNODE_H
